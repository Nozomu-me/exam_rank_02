/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:42:08 by amouassi          #+#    #+#             */
/*   Updated: 2020/10/26 13:55:54 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdio.h>
#include <limits.h>
int ft_putchar(char c)
{
	write(1,&c,1);
	return 1;
}

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i]!= '\0')
		i++;
	return i;
}

int ft_print(char c, int n)
{
	int i = 0;
	while(i<n)
	{
		ft_putchar(c);
		i++;
	}
	return i;
}

int ft_putstr(char *str, int n)
{
	int i = 0;
	while(i<n)
	{
		ft_putchar(str[i]);
		i++;
	}
	return i;
}

int ft_atoi(char *str)
{
	int i = 0;
	int res = 0;
	while(str[i]>='0' && str[i] <= '9')
	{
		res = res*10 + str[i]  - '0';
		i++;
	}
	return res;
}

int ft_countdigit(int n)
{
	int c = 0;
	if(n==0)
		return 1;
	if(n<0)
	{
		n*=-1;
		c++;
	}
	while(n!=0)
	{
		n/=10;
		c++;
	}
	return c;
}

void ft_putnbr(long int n)
{
	if(n>9)
	{
		ft_putnbr(n/10);
		ft_putchar(n%10 + '0');
	}
	else
		ft_putchar(n%10 + '0');
}

int ft_counthexa(unsigned int n)
{
	int c = 0;
	if(n>15)
	{
		c+=ft_counthexa(n/16);
		c+=1;
	}
	else
		c+=1;
	return c;
}

void ft_printhexa(unsigned int n)
{
	if(n>15)
	{
		ft_printhexa(n/16);
		ft_putchar("0123456789abcdef"[n%16]);
	}
	else
		ft_putchar("0123456789abcdef"[n%16]);
}
int print(char c, int n)
{
	int i =0;
	while(i<n)
	{
		ft_putchar(c);
		i++;
	}
	return i;
}

char *ft_substr(char *str, int start, int len)
{
	int  i = 0;
	char *s;
	s = malloc(len + 1);
	if(s == NULL)
		return NULL;
	while(i<len && str[start]!='\0')
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return s;
}

int ft_istype(char c)
{
	return (c=='s' || c== 'x' || c=='d');
}

int ft_isvalid(char c)
{
	return ((c>='0' && c<= '9')||c=='.');
}

typedef struct  s_flags
{
	int w;
	int p;
}				t_flags;

t_flags ft_check(char *str)
{
	int  i = 0;
	t_flags flg;
	flg.w = 0;
	flg.p = -1;
	while(str[i] != '\0')
	{
		if(str[i] >= '0' && str[i] <= '9')
		{
			flg.w = ft_atoi(&str[i]);
			break;
		}
		i++;
	}
	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '.')
			flg.p = ft_atoi(&str[i+1]);
		i++;
	}
	return flg;
}

int ft_string(char *str, va_list *list)
{
	t_flags flg;
	flg = ft_check(str);
	int c ,len;
	c = 0;
	char *s;
	s = va_arg(*list, char *);
	if (s== NULL)
		s = "(null)";
	len = ft_strlen(s);
	if(flg.p < len && flg.p != -1)
		len = flg.p;
	c+=ft_print(' ', flg.w - len);
	c+=ft_putstr(s, len);
	return c;
}

int ft_integer(char *str, va_list *list)
{
	long int n,c,x;
	t_flags flg;
	flg = ft_check(str);
	n = va_arg(*list, int);
	c = ft_countdigit(n);
	x = ft_countdigit(n);
	c = (flg.p == 0 && n== 0) ? --c : c;
	if(flg.p == -1)
	{
		if(n<0)
		{
			c+=ft_print(' ',flg.w - x);
			ft_putchar('-');
			ft_putnbr(n*-1);
		}
		else
		{
			c+=ft_print(' ', flg.w - x);
			ft_putnbr(n);
		}
	}
	if(flg.p >= flg.w)
	{
		if(n<0)
		{
			ft_putchar('-');
			c+=ft_print('0',flg.p - x + 1);
			ft_putnbr(n*-1);
		}
		else
		{
			c+=print('0',flg.p - x);
			if((n == 0 && flg.p != 0) || (n!=0 && flg.p != -1))
				ft_putnbr(n);
		}
	}
	else if(flg.p < flg.w && flg.p != -1)
	{
		if(n<0)
		{
			if(flg.p < flg.w && n!= 0)
				c+=ft_print(' ', flg.w - x);
			else
				c+=ft_print(' ',flg.w - flg.p - 1);
			ft_putchar('-');
			c+=ft_print('0',flg.p - x + 1);
			ft_putnbr(n*-1);
		}
		else
		{
			if(flg.p < flg.w && n!=0)
				c+=ft_print(' ', flg.w - x);
			else
				c+=ft_print(' ',flg.w - flg.p);
			c+=ft_print('0',flg.p - x);
			if((n== 0 && flg.p != 0) || (n!= 0 && flg.p != -1))
				ft_putnbr(n);
		}
	}
	return c;
}

int ft_hexa(char *str, va_list *list)
{
	long int n,c,x;
	t_flags flg;
	flg = ft_check(str);
	n = va_arg(*list, unsigned int);
	c = ft_counthexa(n);
	x = ft_counthexa(n);
	c = (flg.p == 0 && n == 0) ? --c : c;
	if(flg.p == -1)
	{
			c+=ft_print(' ', flg.w - x);
			ft_printhexa(n);
	}
	if(flg.p >= flg.w)
	{
			c+=print('0',flg.p - x);
			if((n == 0 && flg.p != 0) || (n!=0 && flg.p != -1))
				ft_printhexa(n);
	}
	else if(flg.p < flg.w && flg.p != -1)
	{
			if(flg.p < flg.w && n!=0)
				c+=ft_print(' ', flg.w - x);
			else
				c+=ft_print(' ',flg.w - flg.p);
			c+=ft_print('0',flg.p - x);
			if((n== 0 && flg.p != 0) || (n!= 0 && flg.p != -1))
				ft_printhexa(n);
	}
	return c;
}

int ft_subprintf(char *str, int i, int s, int *c, va_list *list)
{
	char *st;
	st = ft_substr(str, i + 1,s-i);
	if(!ft_istype(str[s]))
	{
		*c+=ft_putstr(st,ft_strlen(st));
		i = s + 1;
	}
	if(ft_istype(str[s]))
	{
		if(str[s] == 's')
			*c+=ft_string(st,list);
		if(str[s] == 'd')
			*c+=ft_integer(st,list);
		if(str[s] == 'x')
			*c+=ft_hexa(st, list);
		i = s+1;
	}
	free(st);
	return i;
}

int ft_printf(char *str, ...)
{
	int i , c,s;
	i = 0;
	va_list list;
	va_start(list, str);
	while(str[i]!='\0')
	{
		if(str[i]!='%')
		{
			c+=ft_putchar(str[i]);
			i++;
		}
		else
		{
			s = i + 1;
			while(str[s] !='\0' && ft_isvalid(str[s]))
				s++;
			if(str[s] == '\0')
			{
				c+=ft_putstr(str, ft_strlen(str));
				i = s + 1;
			}
			else
				i = ft_subprintf(str, i, s,&c,&list);
		}
	}
	return c;
}
