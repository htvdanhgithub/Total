#include "..\Utils\Logger.h"
#include "Model.h"

Model::Model(void)
{
}
Model::~Model(void)
{
}
boolean Model::IsStringDigit(const char* str)
{
	for(uint8_t i = 0; i < strlen(str); i++)
	{
		if(!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}
