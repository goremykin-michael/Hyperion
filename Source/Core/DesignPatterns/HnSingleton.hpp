#pragma once
#include <Core/Common/HnIncludes.h>

namespace Hyperion
{
	template <class Type>
	class HnSingleton
	{
	public:
		static Type * Instance()
		{
			if(_pInstance == nullptr)
			{
				_pInstance = new Type();
			}

			return _pInstance;
		}

	protected:
		HnSingleton() {}
		virtual ~HnSingleton() {}

		static Type * _pInstance;
	};

	template <class Type>
	Type *  HnSingleton<Type>::_pInstance = nullptr;
}