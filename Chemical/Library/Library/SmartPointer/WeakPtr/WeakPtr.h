/**
 * @file	WeakPtr.h
 * @brief	ウィークポインタクラス定義
 * @author	morimoto
 */
#ifndef LIB_WEAKPTR_H
#define LIB_WEAKPTR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\SharedPtr\SharedPtr.h"


namespace Lib
{
	/**
	 * ウィークポインタクラス
	 * @tparam Type 管理させるポインタの型
	 */
	template <typename Type>
	class WeakPtr
	{
	public:
		template <typename Type2>
		friend class WeakPtr;

		template <typename Type>
		friend void Reset(WeakPtr<Type>& _ptr, Type* _src);

		template <typename Type>
		friend Type* GetPtr(WeakPtr<Type>& _ptr);

		template <typename Type>
		friend Type** GetPtrPtr(WeakPtr<Type>& _ptr);


		/**
		 * コンストラクタ
		 */
		WeakPtr();

		/**
		 * コンストラクタ
		 * @param[in] _ptr 設定するポインタを管理するシェアドポインタ
		 */
		template <typename ReleaseFunc>
		WeakPtr(SharedPtr<Type, ReleaseFunc>& _ptr);

		/** 
		 * コンストラクタ
		 * @param[in] _ptr 設定するポインタを管理するウィークポインタ
		 */
		WeakPtr(WeakPtr<Type>& _ptr);

		/**
		 * ムーブコンストラクタ
		 * @param[in] _src ムーブ元
		 */
		WeakPtr(WeakPtr<Type>&& _src);

		/**
		 * ムーブコンストラクタ
		 * @param[in] _src ムーブ元
		 */
		template <typename MoveType>
		WeakPtr(WeakPtr<MoveType>&& _src);

		/**
		 * デストラクタ
		 */
		~WeakPtr();


		// キャスト.
		explicit operator bool()
		{
			return m_Ptr != nullptr;
		}


		// 単項演算子.
		Type& operator * ()
		{
			return *m_Ptr;
		}

		Type* operator -> ()
		{
			return m_Ptr;
		}


		// 比較演算子.
		bool operator == (Type* _ptr)
		{
			return m_Ptr == _ptr;
		}

		bool operator != (Type* _ptr)
		{
			return m_Ptr != _ptr;
		}

	private:
		/**
		 * ポインタを設定
		 * @param[in] _ptr 設定するポインタ
		 */
		void ResetResource(Type* _ptr);

		/**
		 * ポインタを取得
		 * @return 管理しているポインタ取得
		 */
		Type* GetResource();

		/**
		 * ポインタのアドレスを取得
		 * @return 管理しているポインタアドレス取得
		 */
		Type** GetResourceAddress();


		Type*	m_Ptr;	//!< 管理するポインタ.

	};


	/**
	 * ポインタの所有権を再設定
	 * @tparam Type 生成するポインタ型
	 * @param[in] _ptr 再設定するポインタ管理オブジェクト
	 * @param[in] _src 設定するポインタ
	 */
	template <typename Type>
	void Reset(WeakPtr<Type>& _ptr, Type* _src = nullptr);

	/**
	 * ポインタの取得
	 * @tparam Type 生成するポインタ型
	 * @param[in] _ptr 取得するポインタの管理オブジェクト
	 */
	template <typename Type>
	Type* GetPtr(WeakPtr<Type>& _ptr);

	/**
	 * ポインタアドレスの取得
	 * @tparam Type 生成するポインタ型
	 * @param[in] _ptr 取得するポインタアドレスの管理オブジェクト
	 */
	template <typename Type>
	Type** GetPtrPtr(WeakPtr<Type>& _ptr);

}


#include "WeakPtr_private.inl"


#endif // !LIB_WEAKPTR_H
