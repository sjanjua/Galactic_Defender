#include "Animator.hpp"
Animator::Animator( int _length, int _height, int _noOfFramePerAnim, int _noOfAnim, float _frameRate)
{
	iLength = _length;
	iHeight = _height;
	iFramesPerAnim = _noOfFramePerAnim;
	iNoOfAnim = _noOfAnim;
	fFrameRate = _frameRate;
	fTime = 0;
	iCurrentFrame = 0;
	iCurrentAnim = 0;
	m_doneAnimating = false;
}
Animator::Animator()
{
	iLength = 128;
	iHeight = 128;
	iFramesPerAnim = 3;
	iNoOfAnim = 1;
	fFrameRate = 5.0f;
	fTime = 0.0f;
	iCurrentFrame = 0;
	iCurrentAnim = 0;
}

void Animator::update(sf::Time dt)
{
	fTime += dt.asSeconds();

	if(fTime > fFrameRate)
	{
		if(iCurrentFrame < iFramesPerAnim-1)
		{
			iCurrentFrame +=1;
			fTime = 0;
		}
		
		else
		{
			iCurrentFrame = 0;
			changeAnim( iCurrentAnim += 1 );
			fTime = 0;
		}
	}
}

sf::IntRect Animator::returnRect()
{
	int x1 , y1;
	x1 = iCurrentFrame * iLength;
	y1 = iCurrentAnim * iHeight;
	return sf::IntRect(x1,y1,iLength,iHeight);
}

void Animator::changeAnim(int i)
{
	if( i > iNoOfAnim )
	{
		iCurrentAnim = 0;
		m_doneAnimating = true;
	}
	
	else if( i < 0)
	{
		iCurrentAnim =0;
	}
	
	else
	{
		iCurrentAnim = i;
	}
}

void Animator::changeFrameRate(float f)
{
	if(f <=0.0f)
	{
		fFrameRate = 0;
	}else{
		fFrameRate = f;
	}
}