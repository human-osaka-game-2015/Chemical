/**
 * @file	Define.h
 * @brief	define定義
 * @author	morimoto
 */
#ifndef DEFINE_H
#define DEFINE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#ifdef _WIN64
#include <Windows.h>
#endif // _WIN64


//----------------------------------------------------------------------
// Define
//----------------------------------------------------------------------

// コピー禁止マクロ.
#define DISALLOW_COPY_AND_ASSIGN(Type)	Type(const Type&);			\
										void operator=(const Type&)

// インターフェースマクロ.
#define interface struct


//----------------------------------------------------------------------
// Template Functions
//----------------------------------------------------------------------
template <typename Type>
inline void SafeDelete(Type*& _type)
{
	typedef char TypeMustBeComplete[sizeof(Type) ? 1 : -1];
	(void) sizeof(TypeMustBeComplete);

	delete _type;
	_type = nullptr;
}

template <typename Type>
inline void SafeDeleteArray(Type*& _type)
{
	typedef char TypeMustBeComplete[sizeof(Type) ? 1 : -1];
	(void) sizeof(TypeMustBeComplete);

	delete[] _type;
	_type = nullptr;
}

template <typename Type>
inline void SafeRelease(Type*& _type)
{
	if (_type != nullptr)
	{
		_type->Release();
		_type = nullptr;
	}
}

template <typename Type>
inline void SafeDestroy(Type*& _type)
{
	if (_type != nullptr)
	{
		_type->Destroy();
		_type = nullptr;
	}
}


//----------------------------------------------------------------------
// Template Functor
//----------------------------------------------------------------------

/**
 * オブジェクト生成ファンクタ
 * @tparam Type 生成するオブジェクト型
 */
template <typename Type>
struct DefaultCreate
{
public:
	template <typename... Args>
	Type* operator()(Args... _args) const
	{
		return new Type(_args...);
	}
};

/**
 * オブジェクト解放ファンクタ
 * @tparam Type 解放するオブジェクト型
 */
template <typename Type>
struct DefaultDelete
{
public:
	void operator()(Type*& _type)
	{
		SafeDelete(_type);
	}
};


#endif // !DEFINE_H
