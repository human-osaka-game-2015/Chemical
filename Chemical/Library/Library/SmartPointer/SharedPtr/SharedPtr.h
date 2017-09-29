/**
 * @file	SharedPtr.h
 * @brief	シェアドポインタクラス定義
 * @author	morimoto
 */
#ifndef LIB_SHAREDPTR_H
#define LIB_SHAREDPTR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Define\Define.h"


namespace Lib
{
	template <typename Type>
	class WeakPtr;

	/**
	 * シェアドポインタクラス
	 * @tparam Type 管理させるポインタの型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 */
	template <
		typename Type,
		typename ReleaseFunc = DefaultDelete<Type>>
	class SharedPtr
	{
	public:
		template <typename Type2, typename ReleaseFunc2>
		friend class SharedPtr;

		template <typename Type>
		friend class WeakPtr;

		template <
			typename Type,
			typename ReleaseFunc>
		friend void Reset(SharedPtr<Type, ReleaseFunc>& _ptr, Type* _src);

		template <
			typename Type,
			typename ReleaseFunc>
		friend Type* GetPtr(SharedPtr<Type, ReleaseFunc>& _ptr);

		template <
			typename Type, 
			typename ReleaseFunc>
		friend Type** GetPtrPtr(SharedPtr<Type, ReleaseFunc>& _ptr);

		template <
			typename Type,
			typename ReleaseFunc>
		friend int GetCounter(SharedPtr<Type, ReleaseFunc>& _ptr);

		template <
			typename Type,
			typename ReleaseFunc>
		friend int* GetCounterPtr(SharedPtr<Type, ReleaseFunc>& _ptr);


		/**
		 * コンストラクタ
		 * @param[in] _ptr 設定するポインタ
		 */
		SharedPtr(Type* _ptr = nullptr);

		/**
		 * コピーコンストラクタ(同じポインタ)
		 * @param[in] _src コピー元
		 */
		SharedPtr(const SharedPtr<Type, ReleaseFunc>& _src);

		/**
		 * コピーコンストラクタ(異なるポインタ)
		 * @param[in] _src コピー元
		 */
		template <typename Type2, typename ReleaseFunc2>
		SharedPtr(const SharedPtr<Type2, ReleaseFunc2>& _src);

		/**
		 * ムーブコンストラクタ(同じポインタ)
		 * @param[in] _src ムーブ元
		 */
		SharedPtr(SharedPtr<Type, ReleaseFunc>&& _src);

		/**
		 * ムーブコンストラクタ(異なるポインタ)
		 * @param[in] _src ムーブ元
		 */
		template <typename Type2, typename ReleaseFunc2>
		SharedPtr(SharedPtr<Type2, ReleaseFunc2>&& _src);

		/**
		 * デストラクタ
		 */
		~SharedPtr();


		// キャスト.
		explicit operator bool()
		{
			return m_Ptr != nullptr;
		}


		// 代入演算子.
		SharedPtr<Type, ReleaseFunc>& operator = (const SharedPtr<Type, ReleaseFunc>& _src)
		{
			// 同じポインタ同士のコピーは行わない.
			if (m_Ptr == _src.m_Ptr) return (*this);

			Release(); // 既に所有しているポインタは解放.

			m_Ptr = _src.m_Ptr;
			m_pRefCount = _src.m_pRefCount;

			AddRef();

			return (*this);
		}


		template <typename Type2, typename ReleaseFunc2>
		SharedPtr<Type, ReleaseFunc>& operator = (const SharedPtr<Type2, ReleaseFunc2>& _src)
		{
			// 同じポインタ同士のコピーは行わない.
			if (m_Ptr == _src.m_Ptr) return (*this);

			Release(); // 既に所有しているポインタは解放.

			m_Ptr = _src.m_Ptr;
			m_pRefCount = _src.m_pRefCount;

			AddRef();

			return (*this);
		}


		// 右辺値の代入.
		SharedPtr<Type, ReleaseFunc>& operator=(SharedPtr<Type, ReleaseFunc>&& _src)
		{
			// 同じポインタ同士のムーブは行わない.
			if (m_Ptr == _src.m_Ptr) return (*this);

			Release(); // 既に所有しているポインタは解放.

			m_Ptr = _src.m_Ptr;
			m_pRefCount = _src.m_pRefCount;

			AddRef();

			Reset(_src);	// 所有権を放棄.

			return (*this);
		}


		template <typename Type2, typename ReleaseFunc2>
		SharedPtr<Type, ReleaseFunc>& operator=(SharedPtr<Type2, ReleaseFunc2>&& _src)
		{
			// 同じポインタ同士のムーブは行わない.
			if (m_Ptr == _src.m_Ptr) return (*this);

			Release(); // 既に所有しているポインタは解放.

			m_Ptr = _src.m_Ptr;
			m_pRefCount = _src.m_pRefCount;

			AddRef();

			Reset(_src);	// 所有権を放棄.

			return (*this);
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

		/**
		 * 参照カウントの取得
		 * @return 参照カウンタ
		 */
		int GetRefCounter();

		/**
		 * 参照カウンタの取得
		 * @return 参照カウンタ
		 */
		int* GetRefCounterPtr();

		/**
		 * 参照カウンタの増分
		 */
		void AddRef();

		/**
		 * ポインタの解放
		 */
		void Release();


		Type*		m_Ptr;			//!< 管理するポインタ.
		int*		m_pRefCount;	//!< 参照カウンタ.

	};


	/**
	 * ポインタの所有権を再設定
	 * @param[in] _ptr 再設定するポインタ管理オブジェクト
	 * @param[in] _src 設定するポインタ
	 */
	template <
		typename Type,
		typename ReleaseFunc>
	void Reset(SharedPtr<Type, ReleaseFunc>& _ptr, Type* _src = nullptr);

	/**
	 * ポインタの取得
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 取得するポインタの管理オブジェクト
	 */
	template <
		typename Type,
		typename ReleaseFunc>
	Type* GetPtr(SharedPtr<Type, ReleaseFunc>& _ptr);

	/**
	 * ポインタアドレスの取得
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 取得するポインタアドレスの管理オブジェクト
	 */
	template <
		typename Type,
		typename ReleaseFunc>
	Type** GetPtrPtr(SharedPtr<Type, ReleaseFunc>& _ptr);

	/**
	 * ポインタの参照数の取得
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 取得するポインタ参照数の管理オブジェクト
	 */
	template <
		typename Type,
		typename ReleaseFunc>
	int GetCounter(SharedPtr<Type, ReleaseFunc>& _ptr);

	/**
	 * ポインタの参照の取得
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 取得するポインタ参照数の管理オブジェクト
	 */
	template <
		typename Type,
		typename ReleaseFunc>
	int* GetCounterPtr(SharedPtr<Type, ReleaseFunc>& _ptr);

	/**
 	 * シェアドポインタ生成関数
	 * @tparam Type 生成するポインタ型
	 * @tparam CreateFunc 生成処理ファンクタ
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @tparam Args 生成する型のコンストラクタ引数の型
	 * @param _args 生成する型のコンストラクタ引数
	 */
	template <
		typename Type,
		typename CreateFunc = DefaultCreate<Type>,
		typename ReleaseFunc = DefaultDelete<Type>,
		typename... Args>
	SharedPtr<Type, ReleaseFunc> CreateSharedPtr(Args... _args);

}


#include "SharedPtr_private.inl"


#endif // !LIB_SHAREDPTR_H
