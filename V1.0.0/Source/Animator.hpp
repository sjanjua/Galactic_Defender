#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP
#include <SFML\Graphics.hpp>

class Animator{
public:

	Animator( int _length, int _height, int _noOfFramePerAnim, int _noOfAnim,float _frameRate );
	Animator();

	void        update( sf::Time dt );
	sf::IntRect returnRect();
	void        changeAnim( int i );
	void        changeFrameRate( float f );

	bool        isDoneAnimating() { return m_doneAnimating ? true : false; }

private:

	int   iFramesPerAnim, iNoOfAnim, iLength, iHeight, iCurrentFrame, iCurrentAnim;
	float fFrameRate;
	float fTime;

	bool  m_doneAnimating;
};
#endif