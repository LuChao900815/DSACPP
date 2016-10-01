#ifndef _FIB_H_
#define _FIB_H_

namespace DSCAPP
{
	class Fib
	{
	private:
		int g,f;
	public:
		Fib(int n)
		{
			f = 1;
			g = 0;
			while(g < n)
			{
				next();
			}
		}
		int get() const
		{
			return g;
		}
		int next()
		{
			g += f;
			f = g - f;
			return g;
		}
		int prev()
		{
			f = g - f;
			g -= f;
			return g;
		}
	};
}
#endif //_FIB_H_