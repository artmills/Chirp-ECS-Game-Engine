#include "inputcomponent.hpp"

void InputComponent::setHorizontalMotion(float input)
{
	horizontalMotion = input;
}
void InputComponent::setVerticalMotion(float input)
{
	verticalMotion = input;
}
void InputComponent::setDepthMotion(float input)
{
	depthMotion = input;
}

float InputComponent::getHorizontalMotion()
{
	return horizontalMotion;
}
float InputComponent::getVerticalMotion()
{
	return verticalMotion;
}
float InputComponent::getDepthMotion()
{
	return depthMotion;
}

void InputComponent::Reset()
{
	horizontalMotion = 0;
	verticalMotion = 0;
	depthMotion = 0;
}
