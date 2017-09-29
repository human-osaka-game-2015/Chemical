/**
 * @file	UniquePtr_private.inl
 * @brief	ユニークポインタクラス実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	UniquePtr<Type, ReleaseFunc>::UniquePtr(Type* _ptr) :
		m_Ptr(_ptr)
	{
	}


	//----------------------------------------------------------------------
	// Move Constructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	UniquePtr<Type, ReleaseFunc>::UniquePtr(UniquePtr<Type, ReleaseFunc>&& _src)
	{
		m_Ptr = _src.m_Ptr;

		_src.m_Ptr = nullptr;	// 所有権を放棄.
	}

	template <typename Type, typename ReleaseFunc>
	template <typename Type2, typename ReleaseFunc2>
	UniquePtr<Type, ReleaseFunc>::UniquePtr(UniquePtr<Type2, ReleaseFunc2>&& _src)
	{
		m_Ptr = _src.m_Ptr;

		_src.m_Ptr = nullptr;	// 所有権を放棄.
	}


	//----------------------------------------------------------------------
	// Destructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	UniquePtr<Type, ReleaseFunc>::~UniquePtr()
	{
		Release();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	void UniquePtr<Type, ReleaseFunc>::ResetResource(Type* _ptr)
	{
		Release();	// 既に所有しているポインタは解放.

		m_Ptr = _ptr;
	}

	template <typename Type, typename ReleaseFunc>
	Type* UniquePtr<Type, ReleaseFunc>::GetResource()
	{
		return m_Ptr;
	}

	template <typename Type, typename ReleaseFunc>
	Type** UniquePtr<Type, ReleaseFunc>::GetResourceAddress()
	{
		return &m_Ptr;
	}

	template <typename Type, typename ReleaseFunc>
	void UniquePtr<Type, ReleaseFunc>::Release()
	{
		ReleaseFunc Functor;
		Functor(m_Ptr);
	}


	//----------------------------------------------------------------------
	// Friend Functions
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	void Reset(UniquePtr<Type, ReleaseFunc>& _ptr, Type* _src)
	{
		_ptr.ResetResource(_src);
	}

	template <typename Type, typename ReleaseFunc>
	Type* GetPtr(UniquePtr<Type, ReleaseFunc>& _ptr)
	{
		return _ptr.GetResource();
	}

	template <typename Type, typename ReleaseFunc>
	Type** GetPtrPtr(UniquePtr<Type, ReleaseFunc>& _ptr)
	{
		return _ptr.GetResourceAddress();
	}

	template <typename Type, typename CreateFunc, typename ReleaseFunc, typename... Args>
	UniquePtr<Type, ReleaseFunc> CreateUniquePtr(Args... _args)
	{
		// 生成ファンクタからオブジェクトを生成.
		return UniquePtr<Type, ReleaseFunc>(CreateFunc(_args...));
	}
}

