/**
 * @file	WeakPtr_private.inl
 * @brief	ウィークポインタクラス実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
	template <typename Type>
	WeakPtr<Type>::WeakPtr() :
		m_Ptr(nullptr)
	{
	}

	template <typename Type>
	template <typename ReleaseFunc>
	WeakPtr<Type>::WeakPtr(SharedPtr<Type, ReleaseFunc>& _ptr) :
		m_Ptr(_ptr.m_Ptr)
	{
	}


	//----------------------------------------------------------------------
	// Copy Constructor
	//----------------------------------------------------------------------
	template <typename Type>
	WeakPtr<Type>::WeakPtr(WeakPtr<Type>& _src)
	{
		m_Ptr = _src.m_Ptr;
	}


	//----------------------------------------------------------------------
	// Move Constructor
	//----------------------------------------------------------------------
	template <typename Type>
	WeakPtr<Type>::WeakPtr(WeakPtr<Type>&& _src)
	{
		m_Ptr = _src.m_Ptr;

		_src.m_Ptr = nullptr;	// 所有権を放棄.
	}

	template <typename Type>
	template <typename MoveType>
	WeakPtr<Type>::WeakPtr(WeakPtr<MoveType>&& _src)
	{
		m_Ptr = _src->m_Ptr;

		_src.m_Ptr = nullptr;	// 所有権を放棄.
	}

	//----------------------------------------------------------------------
	// Destructor
	//----------------------------------------------------------------------
	template <typename Type>
	WeakPtr<Type>::~WeakPtr()
	{
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	template <typename Type>
	void WeakPtr<Type>::ResetResource(Type* _ptr)
	{
		m_Ptr = _ptr;
	}

	template <typename Type>
	Type* WeakPtr<Type>::GetResource()
	{
		return m_Ptr;
	}

	template <typename Type>
	Type** WeakPtr<Type>::GetResourceAddress()
	{
		return &m_Ptr;
	}


	//----------------------------------------------------------------------
	// Friend Functions
	//----------------------------------------------------------------------
	template <typename Type>
	void Reset(WeakPtr<Type>& _ptr, Type* _src)
	{
		_ptr.ResetResource(_src);
	}

	template <typename Type>
	Type* GetPtr(WeakPtr<Type>& _ptr)
	{
		return _ptr.GetResource();
	}

	template <typename Type>
	Type** GetPtrPtr(WeakPtr<Type>& _ptr)
	{
		return _ptr.GetResourceAddress();
	}
}
