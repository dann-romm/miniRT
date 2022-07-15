#include "utils_ft.h"

int	ft_atof(const char *str, double *result)
{
	int		integer;
	double	fraction;
	int		pow;

	if (ft_atoi(str, &integer))
		return (1);
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '.')
	{
		str++;
		if (*str < '0' || *str > '9')
			return (1);
		ft_atoi(str, &pow);
		fraction = (double)pow;
		pow = 0;
		while (*str >= '0' && *str <= '9')
		{
			str++;
			pow++;
		}
		while (pow > 0)
		{
			fraction /= 10;
			pow--;
		}
	}
	if (integer < 0)
		fraction *= -1;
	*result = (double)integer + fraction;
	return (0);
}
