/**
 * @file	SharedPtr_private.inl
 * @brief	シェアドポインタクラス実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	SharedPtr<Type, ReleaseFunc>::SharedPtr(Type* _ptr) :
		m_Ptr(_ptr),
		m_pRefCount(new int)
	{
		*m_pRefCount = 0;
		AddRef();
	}


	//----------------------------------------------------------------------
	// Copy Constructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	SharedPtr<Type, ReleaseFunc>::SharedPtr(const SharedPtr<Type, ReleaseFunc>& _src)
	{
		m_Ptr = _src.m_Ptr;
		m_pRefCount = _src.m_pRefCount;

		AddRef();
	}

	template <typename Type, typename ReleaseFunc>
	template <typename Type2, typename ReleaseFunc2>
	SharedPtr<Type, ReleaseFunc>::SharedPtr(const SharedPtr<Type2, ReleaseFunc2>& _src)
	{
		m_Ptr = _src.m_Ptr;
		m_pRefCount = _src.m_pRefCount;

		AddRef();
	}


	//----------------------------------------------------------------------
	// Move Constructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	SharedPtr<Type, ReleaseFunc>::SharedPtr(SharedPtr<Type, ReleaseFunc>&& _src)
	{
		m_Ptr = _src.m_Ptr;
		m_pRefCount = _src.m_pRefCount;

		AddRef();

		Reset(_src);	//!< 右辺値が持つ所有権は放棄.
	}

	template <typename Type, typename ReleaseFunc>
	template <typename Type2, typename ReleaseFunc2>
	SharedPtr<Type, ReleaseFunc>::SharedPtr(SharedPtr<Type2, ReleaseFunc2>&& _src)
	{
		m_Ptr = _src.m_Ptr;
		m_pRefCount = _src.m_pRefCount;

		AddRef();

		Reset(_src);	//!< 右辺値が持つ所有権は放棄.
	}


	//----------------------------------------------------------------------
	// Destructor
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	SharedPtr<Type, ReleaseFunc>::~SharedPtr()
	{
		Release();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	void SharedPtr<Type, ReleaseFunc>::ResetResource(Type* _ptr)
	{
		Release();	// 既に所有しているポインタの所有権は手放す.

		m_Ptr = _ptr;
		m_pRefCount = new int;
		*m_pRefCount = 0;
		AddRef();
	}

	template <typename Type, typename ReleaseFunc>
	Type* SharedPtr<Type, ReleaseFunc>::GetResource()
	{
		return m_Ptr;	// 管理するポインタを返す.
	}

	template <typename Type, typename ReleaseFunc>
	Type** SharedPtr<Type, ReleaseFunc>::GetResourceAddress()
	{
		return &m_Ptr;	// 管理するポインタのアドレスを返す.
	}

	template <typename Type, typename ReleaseFunc>
	int SharedPtr<Type, ReleaseFunc>::GetRefCounter()
	{
		return *m_pRefCount;
	}

	template <typename Type, typename ReleaseFunc>
	int* SharedPtr<Type, ReleaseFunc>::GetRefCounterPtr()
	{
		return m_pRefCount;
	}

	template <typename Type, typename ReleaseFunc>
	void SharedPtr<Type, ReleaseFunc>::AddRef()
	{
		(*m_pRefCount)++;
	}

	template <typename Type, typename ReleaseFunc>
	void SharedPtr<Type, ReleaseFunc>::Release()
	{
		(*m_pRefCount)--;

		if ((*m_pRefCount) == 0)
		{
			// 参照カウンタが0なら解放処理を行う.
			ReleaseFunc Functor;
			Functor(m_Ptr);
			SafeDelete(m_pRefCount);
		}

		m_Ptr = nullptr;
		m_pRefCount = nullptr;
	}



	//----------------------------------------------------------------------
	// Friend Functions
	//----------------------------------------------------------------------
	template <typename Type, typename ReleaseFunc>
	void Reset(SharedPtr<Type, ReleaseFunc>& _ptr, Type* _src)
	{
		_ptr.ResetResource(_src);
	}

	template <typename Type, typename ReleaseFunc>
	Type* GetPtr(SharedPtr<Type, ReleaseFunc>& _ptr)
	{
		return _ptr.GetResource();
	}

	template <typename Type, typename ReleaseFunc>
	Type** GetPtrPtr(SharedPtr<Type, ReleaseFunc>& _ptr)
	{
		return _ptr.GetResourceAddress();
	}

	template <typename Type, typename ReleaseFunc>
	int GetCounter(SharedPtr<Type, ReleaseFunc>& _ptr)
	{
		return _ptr.GetRefCounter();
	}

	template <typename Type, typename ReleaseFunc>
	int* GetCounterPtr(SharedPtr<Type, ReleaseFunc>& _ptr)
	{
		return _ptr.GetRefCounterPtr();
	}

	template <typename Type, typename CreateFunc, typename ReleaseFunc, typename... Args>
	SharedPtr<Type, ReleaseFunc> CreateSharedPtr(Args... _args)
	{
		// 生成ファンクタからオブジェクトを生成.
		return SharedPtr<Type, ReleaseFunc> pSmartPtr(CreateFunc(_args...));
	}
}
