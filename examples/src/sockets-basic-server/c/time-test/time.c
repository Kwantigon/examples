#include <stdio.h>
#include <time.h>

void main() {
	time_t time_now;
	time(&time_now);
	printf("Seconds: %ld\n", time_now);

	struct tm* t_info;
	t_info = localtime(&time_now);

	int sec = t_info->tm_sec;
	int min = t_info->tm_min;
	int hour = t_info->tm_hour;
	printf("%d:%d:%d\n", hour, min, sec);

	int DD = t_info->tm_mday;
	int MM = t_info->tm_mon;
	int YY = t_info->tm_year;
	printf("%d:%d:%d\n", 1900+YY, MM, DD);
}
