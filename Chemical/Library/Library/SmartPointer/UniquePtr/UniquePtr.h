/**
 * @file	UniquePtr.h
 * @brief	ユニークポインタクラス定義
 * @author	morimoto
 */
#ifndef LIB_UNIQUEPTR_H
#define LIB_UNIQUEPTR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Define\Define.h"


namespace Lib
{
	/**
	 * ユニークポインタクラス
	 * @tparam Type 管理させるポインタの型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 */
	template <
		typename Type,
		typename ReleaseFunc = DefaultDelete<Type>>
	class UniquePtr
	{
	public:
		template <typename Type2, typename ReleaseFunc2>
		friend class UniquePtr;

		template <
			typename Type,
			typename ReleaseFunc>
		friend void Reset(UniquePtr<Type, ReleaseFunc>& _ptr, Type* _src);

		template <
			typename Type,
			typename ReleaseFunc>
		friend Type* GetPtr(UniquePtr<Type, ReleaseFunc>& _ptr);

		template <
			typename Type,
			typename ReleaseFunc>
		friend Type** GetPtrPtr(UniquePtr<Type, ReleaseFunc>& _ptr);


		/**
		 * コンストラクタ
		 * @param[in] _ptr 設定するポインタ
		 */
		UniquePtr(Type* _ptr = nullptr);

		/**
		 * ムーブコンストラクタ(同じポインタ)
		 * @param[in] _src ムーブ元
		 */
		UniquePtr(UniquePtr<Type, ReleaseFunc>&& _src);

		/**
		 * ムーブコンストラクタ(異なるポインタ)
		 * @param[in] _src ムーブ元
		 */
		template <typename Type2, typename ReleaseFunc2>
		UniquePtr(UniquePtr<Type2, ReleaseFunc2>&& _src);

		/**
		 * デストラクタ
		 */
		~UniquePtr();


		// キャスト.
		explicit operator bool()
		{
			return m_Ptr != nullptr;
		}


		// 右辺値の代入.
		UniquePtr<Type, ReleaseFunc>& operator=(UniquePtr<Type, ReleaseFunc>&& _src)
		{
			// 同じポインタ同士のムーブは行わない.
			if (m_Ptr == _src.m_Ptr) return (*this);

			Release(); // 既に所有しているポインタは解放.

			m_Ptr = _src.m_Ptr;
			_src.m_Ptr = nullptr;	// 所有権を放棄.

			return (*this);
		}


		template <typename Type2, typename ReleaseFunc2>
		UniquePtr<Type, ReleaseFunc>& operator=(UniquePtr<Type2, ReleaseFunc2>&& _src)
		{
			// 同じポインタ同士のムーブは行わない.
			if (m_Ptr == _src.m_Ptr) return (*this);

			Release(); // 既に所有しているポインタは解放.

			m_Ptr = _src.m_Ptr;
			_src.m_Ptr = nullptr;	// 所有権を放棄.

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
		 * ポインタの解放
		 */
		void Release();


		Type* m_Ptr; //!< 管理するポインタ.


		// コピー禁止.
		UniquePtr<Type, ReleaseFunc>(const UniquePtr<Type, ReleaseFunc>&);
		void operator=(const UniquePtr<Type, ReleaseFunc>&);

	};


	/**
	 * ポインタの所有権を再設定
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 再設定するポインタ管理オブジェクト
	 * @param[in] _src 設定するポインタ
	 */
	template <
		typename Type,
		typename ReleaseFunc>
	void Reset(UniquePtr<Type, ReleaseFunc>& _ptr, Type* _src = nullptr);

	/**
	 * ポインタの取得
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 取得するポインタの管理オブジェクト
	 */
	template <
		typename Type, 
		typename ReleaseFunc>
	Type* GetPtr(UniquePtr<Type, ReleaseFunc>& _ptr);

	/**
	 * ポインタアドレスの取得
	 * @tparam Type 生成するポインタ型
	 * @tparam ReleaseFunc 解放処理ファンクタ
	 * @param[in] _ptr 取得するポインタアドレスの管理オブジェクト
	 */
	template <
		typename Type, 
		typename ReleaseFunc>
	Type** GetPtrPtr(UniquePtr<Type, ReleaseFunc>& _ptr);

	/**
 	 * ユニークポインタ生成関数
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
	UniquePtr<Type, ReleaseFunc> CreateUniquePtr(Args... _args);

}


#include "UniquePtr_private.inl"


#endif // !LIB_UNIQUEPTR_H
