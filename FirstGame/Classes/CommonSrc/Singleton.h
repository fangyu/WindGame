/*
 * Singleton.h
 *
 *  Created on: 2013Äê9ÔÂ12ÈÕ
 *      Author: zengjf
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template <typename T>
class Singleton
{
public:
	~Singleton()
	{

	}

	static T * Instance()
	{
		if (0 == ms_pInstance)
		{
			ms_pInstance = new T;
		}

		return ms_pInstance;
	}

	static void DestroyInstance()
	{
		if (ms_pInstance) {
			delete ms_pInstance;
			ms_pInstance = 0;
		}
	}

private:

	static T *		ms_pInstance;
};

template< class T > T * ::Singleton<T>::ms_pInstance = 0;


#endif /* SINGLETON_H_ */
