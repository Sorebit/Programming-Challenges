// BMI Calculator
// Written as part of /g/'s programming challenge
//
// Reference: https://en.wikipedia.org/wiki/Body_mass_index
//
// Metric BMI = ( weight (kg) / ( height (m) ^2 ) )
// Imperial BMI = ( weight (lb) / ( height (in) ^2) ) x 703
//
//           Category                       BMI (kg/m2)   BMI Prime
//                                          from   to     from   to
// Very severely underweight                       15            0.60
// Severely underweight                     15     16     0.60   0.64
// Underweight 	                            16     18.5   0.64   0.74
// Normal (healthy weight)                  18.5   25     0.74   1.0
// Overweight                               25     30     1.0    1.2
// Obese Class I (Moderately obese)         30     35     1.2    1.4
// Obese Class II (Severely obese)          35     40     1.4    1.6
// Obese Class III (Very severely obese)    40            1.6
//
// I don't use BMI Prime here 
//
// Reference: http://www.bmi3d.com/table.html
// Normal (healthy) BMI by age
//  Age      BMI
// 19–24    19–24
// 25–34    20–25
// 35–44    21–26
// 45–54    22–27
// 55–64    23–28
// 65-      24–29
//
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>
#include <ncurses.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

// Flush input buffer
void flush_readahead(void)
{
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

// Print some text, then read to tr of specified type from stdin 
// Repeat untill valid
void input(char* text, char* type, void* tr)
{
	int err;
	do
	{
		printf("%s", text);
		err = scanf(type, tr);
		flush_readahead();
	} while(!err);
}

// Depending on min and max, print category of bmi
void category(float bmi, float min, float max)
{
	printf("Your BMI is " BLU "%.2f" RESET "\n", bmi);
	printf("At your age it means you are ");
	if(bmi < min)
		printf(RED "UNDERWEIGHT" RESET "\n");
	else if(bmi > max)
		printf(RED "OVERWEIGHT" RESET "\n");
	else
		printf(GRN "HEALTHY" RESET "\n");
}

int main(int argc, char const *argv[])
{	
	int opt;
	float weight, height, bmi, age;

	// Greeting
	printf("BMI Calculator - Sorbet\n");
	printf("Written as part of /g/'s programming chalenges\n\n");

	// Metric or imperial
	do
	{
		printf("Would you like to use (1) metric or (2) imperial system?\n");
		printf("Input '1' or '2': ");
		opt = 0;
		scanf("%d", &opt);
		flush_readahead();
	} while(opt != 1 && opt != 2);

	// Metric
	if(opt == 1)
	{
		input("Input your weight in [kg]: ", "%f", &weight);
		input("Input height in [cm]: ", "%f", &height);
		bmi = 10000 * weight / (height*height);
	}
	// Imperial
	else
	{
		input("Input your weight in [lb]: ", "%f", &weight);
		input("Input height in [in]: ", "%f", &height);
		bmi = 703 * weight / (height*height);
	}

	// Age is used to offset the normal curve
	input("Input your age: ", "%f", &age);

	if     (age >= 65) category(bmi, 24, 29);
	else if(age >= 55) category(bmi, 23, 28);
	else if(age >= 45) category(bmi, 22, 27);
	else if(age >= 35) category(bmi, 21, 26);
	else if(age >= 25) category(bmi, 20, 25);
	else               category(bmi, 19, 24);


	return 0;
}