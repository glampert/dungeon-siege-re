//////////////////////////////////////////////////////////////////////////////
//
// File     :  dsdll.h
// Author(s):  Scott Bilas
//
// Summary  :  Contains macros to make DSDLL'ing easier...
//
// Copyright © 2002 Gas Powered Games, Inc.  All rights reserved.
//----------------------------------------------------------------------------
//  $Revision:: $              $Date:$
//----------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef __DSDLL_H
#define __DSDLL_H

#include "assert.h"

//////////////////////////////////////////////////////////////////////////////
// Usage documentation

/*	+++																	+++
	+++								EXPORTING							+++
	+++																	+++

	*** Exporting Functions to FuBi ***

		To export a function for Skrit, just tag it with FEX, like this:

			FEX void MyFunction( const char* text );

		Note that class methods can also be exported.

	*** Exporting Variables to FuBi ***

		Skrit is able to expose pairs of Set/Get functions as simple variables
		to scripts (this concept copied from JavaBeans). In order for this to
		work right, you need to provide two functions, like this:

			FEX int  GetSomeVariable( void ) const;
			FEX void SetSomeVariable( int );

		These will be exposed as a single variable called "SomeVariable" and is
		a member of whatever class these are members of. An easier way to do
		this directly is to use the FUBI_VARIABLE() macros, like this:

			FUBI_VARIABLE( int, m_, SomeVariable , "This is just a variable" );

		This will export Set and Get functions in addition to declaring the
		variable itself at the current access level of the class.

	*** Exporting Classes to FuBi ***

		FuBi supports passing pointers to just about anything - internally it's
		just a DWORD.

	*** Renaming exported FuBi functions ***

		It's sometimes necessary to export a function to FuBi that has the same
		name as another existing function to avoid a collision. This can be done
		using the FUBI_RENAME macro, like this:

			virtual void SomeFunction( void ) const;
			FEX void FUBI_RENAME( SomeFunction )( void ) const
				{  SomeFunction();  }

		Generally this will be used for wrapper functions, especially in the
		case of virtual functions, which can't be FuBi-exported directly, but
		instead must be called indirectly through a separate wrapper.

	*** Exporting a POD (plain old data) type to FuBi ***

		Use the FUBI_POD_CLASS() macro to tell FuBi that your class/struct is to
		be considered "plain old data", meaning that its constructors and
		destructor don't do anything (if it has any).

	+++																	+++
	+++							DOCUMENTATION							+++
	+++																	+++

	*** FuBi Documentation ***

		All functions, classes, and variables can be documented with FuBi. The
		purpose of documenting these is to help out scripting. A doc'd function
		can be queried for what it does, and the parameters it takes. Some FuBi
		macros take a "DOCS" parameter, which is a general doc on the entire
		function or variable, and a "PARAMS" parameter, which is a comma- or
		space- delimited list of names for each of the variables that the
		function takes. NOTE: pay attention to the parameter documentation and
		where the commas actually are! Example usage:

			FEX float         Foo( float f, int i );
			FUBI_MEMBER_DOC ( Foo,      "f,"   "i", "Do something with 'f' then 'i'." );

		The FUBI_DOC and FUBI_MEMBER_DOC macros suffer a minor limitation wrt
		overloaded function names, and must be postfixed with some unique id to
		differentiate them (generally an int is ok), like this:

			FEX float         Foo( float f );
			FUBI_MEMBER_DOC(  Foo$0,    "f", "First overloaded function." );
			FEX float         Foo( float f, int i );
			FUBI_MEMBER_DOC(  Foo$1,    "f,"   "i", "First overloaded function." );

	+++																	+++
	+++								RULES								+++
	+++																	+++

	*** General Restrictions ***

		FuBi is fairly general purpose. These are specifically supported:

			Functions with external linkage - this includes nonstatic global
			functions and static or nonstatic class member functions. They may
			be overloaded.

			Any number of parameters per function, including variable argument
			(...) lists. Exported functions can also return parameters.

			All built-in types (char, int, float, etc.) are supported for
			parameters or return values.

			Strings (const char*) are specifically supported through some
			special case code.

			Pointers and references to user-defined types (classes, structs etc)
			are ok as parameters and return values.

		There are also some important restrictions:

			__fastcall is not supported as a calling convention.

			Don't prefix any names with FUBI_ or allow any names to contain '$'
			in the middle of the name - these are reserved as special tags that
			FuBi uses for documentation and internal functions attached to
			exports.

			Skrit is case-insensitive and FuBi has to accommodate this. Do not
			export two functions with the same name but different case (for
			example, Test() and TEST()).

			For consistency reasons, do not use underscores in any exported
			names - some_function_call() is bad, SomeFunctionCall() is good.

			If a SetXXX and GetXXX pair exists but the parameters do not match
			as described above in "Exporting Variables" it will print an error.

			"Complicated" exports won't even parse properly and you'll get an
			error from FuBi about how it isn't able to understand some function
			you're trying to export. This will typically happen with templates
			or functions that take function pointers as parameters. Not
			supported. Specific templates (such as callbacks) will be supported
			as they become necessary - let me know.

			Unions are not supported. Never will be.

			Passing complex types by value is not supported. If you export a
			function that takes a GUID by value, you'll get an error. Pass it
			by reference and it'll be okay. Specific support can be added to
			allow passing these by value if you tag the type as POD (and it
			really has to be plain old data! no ctor/dtors called!).

			Virtual functions are supported but are very unsafe. A virtual
			function exported to FuBi will get called directly. The vtbl is not
			consulted ('cause I don't know how to query its contents without a 
			PDB) to figure out which version of the function to call. To prevent
			Bad Things happening from this I issue a warning for exported
			virtual functions. Work around this by exporting a non- virtual
			function that just redirects the call to a virtual function. Then
			the compiler will do the proper vtbl work. Use FUBI_RENAME to give
			it the same name as the virtual function from Skrit's point of view.

			Sometimes the DbgHelp.dll symbol undecoration code just bugs out.
			This happens more often on Win9x for some reason. Let me know of any
			weird cases.

			Exports of constructors, destructors and overloaded operators are
			not supported.

			Exporting functions from nested classes and namespaces is not
			supported, mainly because Skrit doesn't need this complication.

			Data exports (exporting a variable directly rather than using
			FUBI_VARIABLE) will always get warnings. Don't export data.
*/

//////////////////////////////////////////////////////////////////////////////
// macro definitions

// Function macros.

	// general purpose fubi exporter
#	define FEX __declspec ( dllexport )

	// note that the weird helper function here is required to avoid exporting
	// all kinds of extra stuff if those constants were to be embedded in the
	// exported function. strange but it works...

#	define FUBI_DOC( NAME, PARAMS, DOCS ) \
		inline const FuBi::FunctionDocs& NAME##$QueryDocsHelper( void ) \
			{  static const FuBi::FunctionDocs sDocs( PARAMS, DOCS );  return ( sDocs );  } \
		FEX inline const FuBi::FunctionDocs& __cdecl NAME##$QueryDocs( void ) \
			{  return ( NAME##$QueryDocsHelper() );  }

#	define FUBI_MEMBER_DOC( NAME, PARAMS, DOCS ) \
		static const FuBi::FunctionDocs& NAME##$QueryDocsHelper( void ) \
			{  static const FuBi::FunctionDocs sDocs( PARAMS, DOCS );  return ( sDocs );  } \
		FEX static const FuBi::FunctionDocs& __cdecl NAME##$QueryDocs( void ) \
			{  return ( NAME##$QueryDocsHelper() );  }

#	define FUBI_RENAME( NAME ) FUBI_RENAME_##NAME

// Variable macros.

	// this will generate: GetFoo(), SetFoo(), and add a m_Foo, where "Foo" is NAME,
	//  the type is T, and the prefix on the variable is m_.

#	define FUBI_VARIABLE( T, PREFIX, NAME, DOCS ) \
		FEX T Get##NAME( void ) const  {  return ( PREFIX##NAME );  } \
		FEX void Set##NAME( T v  )  {  PREFIX##NAME = v;  } \
		FUBI_MEMBER_DOC( Get##NAME, "", DOCS ); \
		T PREFIX##NAME

#	define FUBI_VARIABLE_BYREF( T, PREFIX, NAME, DOCS ) \
		FEX const T& Get##NAME( void ) const  {  return ( PREFIX##NAME );  } \
		FEX void Set##NAME( const T& v  )  {  PREFIX##NAME = v;  } \
		FUBI_MEMBER_DOC( Get##NAME, "", DOCS ); \
		T PREFIX##NAME

#	define FUBI_VARIABLE_READONLY( T, PREFIX, NAME, DOCS ) \
		FEX T Get##NAME( void ) const  {  return ( PREFIX##NAME );  } \
		FUBI_MEMBER_DOC( Get##NAME, "", DOCS ); \
		T PREFIX##NAME

#	define FUBI_VARIABLE_BYREF_READONLY( T, PREFIX, NAME, DOCS ) \
		FEX const T& Get##NAME( void ) const  {  return ( PREFIX##NAME );  } \
		FUBI_MEMBER_DOC( Get##NAME, "", DOCS ); \
		T PREFIX##NAME

#	define FUBI_VARIABLE_WRITEONLY( T, PREFIX, NAME, DOCS ) \
		FEX void Set##NAME( T v  )  {  PREFIX##NAME = v;  } \
		FUBI_MEMBER_DOC( Set##NAME, "", DOCS ); \
		T PREFIX##NAME

#	define FUBI_VARIABLE_BYREF_WRITEONLY( T, PREFIX, NAME, DOCS ) \
		FEX void Set##NAME( const T& v  )  {  PREFIX##NAME = v;  } \
		FUBI_MEMBER_DOC( Set##NAME, "", DOCS ); \
		T PREFIX##NAME

// Class macros.

	// class doco

#	define FUBI_CLASS_DOC( T, DOCS ) \
		FUBI_MEMBER_DOC( CLASSDOCO, "", DOCS )

	// inheritance

#	define FUBI_CLASS_INHERIT_IMPL( T, BASE, NAME ) \
		FEX static int __cdecl NAME( BASE* ) \
			{  return ( (int)(BASE*)(T*)1 - (int)(T*)1 );  }

#	define FUBI_CLASS_INHERIT( T, BASE ) \
		FUBI_CLASS_INHERIT_IMPL( T, BASE, FUBI_Inheritance )

#	define FUBI_CLASS_INHERIT2( T, BASE1, BASE2 ) \
		FUBI_CLASS_INHERIT_IMPL( T, BASE1, FUBI_Inheritance$0 ) \
		FUBI_CLASS_INHERIT_IMPL( T, BASE2, FUBI_Inheritance$1 )

#	define FUBI_CLASS_INHERIT3( T, BASE1, BASE2, BASE3 ) \
		FUBI_CLASS_INHERIT2( T, BASE1, BASE2 ) \
		FUBI_CLASS_INHERIT_IMPL( T, BASE3, FUBI_Inheritance$2 )

#	define FUBI_CLASS_INHERIT4( T, BASE1, BASE2, BASE3, BASE4 ) \
		FUBI_CLASS_INHERIT3( T, BASE1, BASE2, BASE3 ) \
		FUBI_CLASS_INHERIT_IMPL( T, BASE4, FUBI_Inheritance$3 )

	// singleton classes

#	define FUBI_SINGLETON_CLASS_IMPL( T ) \
		FEX static T* __cdecl FUBI_GetClassSingleton( void ) \
			{  return ( &GetSingleton() );  }

#	define FUBI_SINGLETON_CLASS( T, DOCS ) \
		FUBI_SINGLETON_CLASS_IMPL( T ) \
		FUBI_CLASS_DOC( T, DOCS )

#	define FUBI_SINGLETON_NESTED_CLASS( T, NAME, DOCS ) \
		FUBI_SINGLETON_CLASS_IMPL( T ) \
		FUBI_CLASS_DOC( NAME, DOCS )

	// POD classes

#	define FUBI_POD_CLASS( T ) \
		FEX static size_t __cdecl FUBI_PodGetSize( void ) \
			{  return ( sizeof( T ) );  }

//////////////////////////////////////////////////////////////////////////////
// FuBi API declarations

namespace FuBi
{

// used for function doco
struct FunctionDocs
{
	const char* m_ParamDocs;
	const char* m_FunctionDocs;

	FunctionDocs( const char* paramDocs, const char* functionDocs )
	{
		m_ParamDocs    = paramDocs;
		m_FunctionDocs = functionDocs;
	}
};

}	// end of FuBi namespace

//////////////////////////////////////////////////////////////////////////////
// class Singleton <T> declaration

// this is a simple singleton tracking class. it asserts on attempts to deref
//  an invalid singleton and if you instantiate more than one. auto-unregisters
//  the object on destruction. note: this is from my game gem, for more info
//  see:
//
//  http://www.drizzle.com/~scottb/publish/gpgems1_singleton.htm

// usage - only one step!:
//
//     class MyClass : public Singleton <MyClass>			<-- derive from Singleton <YourClassNameHere>
//     {
//     public:
//         void Foo( void );
//         ...
//     };
//
//     void SomeFunction( void )
//     {
//         MyClass::GetSingleton().Foo();					<-- easy, eh?
//     }
//
// for more convenience, you can always do something like this:
//
//     #define gMyClass MyClass::GetSingleton()
//
// ...then it's like a global: gMyClass.Foo()...
//

template <typename T>
class Singleton
{
protected:
	Singleton( void )
	{
		assert( ms_Singleton == NULL );
		int offset = (int)(T*)1 - (int)(Singleton <T> *)(T*)1;
		ms_Singleton = (T*)((int)this + offset);
	}
   ~Singleton( void )  {  assert( ms_Singleton != NULL );  ms_Singleton = NULL;  }

public:
	static T&   GetSingleton      ( void )  {  assert( ms_Singleton != NULL );  return ( *ms_Singleton );  }
	static T*   GetSingletonPtr   ( void )  {  return ( ms_Singleton );  }
	static bool DoesSingletonExist( void )  {  return ( ms_Singleton != NULL );  }

private:
	static T* ms_Singleton;

	// do not permit auto-generation of these funcs
	Singleton( const Singleton <T> & );
	Singleton <T> & operator = ( const Singleton <T> & );
};

template <typename T> T* Singleton <T>::ms_Singleton = NULL;

//////////////////////////////////////////////////////////////////////////////
// class AutoSingleton <T> declaration

// purpose: a Singleton that automatically instantiates itself (statically).
//          nothing special about this class - it just provides the same
//          interface as a normal Singleton.

template <typename T>
class AutoSingleton
{
protected:
	AutoSingleton( void )
	{
		assert( ms_Singleton == NULL );
		ms_Singleton = &ms_SingletonInstance;
	}
   ~AutoSingleton( void )
	{
		assert( ms_Singleton != NULL );
		ms_Singleton = NULL;
	}

public:
	static T&   GetSingleton      ( void )  {  assert( ms_Singleton != NULL );  return ( *ms_Singleton );  }
	static T*   GetSingletonPtr   ( void )  {  return ( ms_Singleton );  }
	static bool DoesSingletonExist( void )  {  return ( ms_Singleton != NULL );  }

private:
	static T* ms_Singleton;
	static T ms_SingletonInstance;

	// do not permit auto-generation of these funcs
	AutoSingleton( const AutoSingleton <T> & );
	AutoSingleton <T> & operator = ( const AutoSingleton <T> & );
};

template <typename T> T* AutoSingleton <T>::ms_Singleton = NULL;
template <typename T> T AutoSingleton <T>::ms_SingletonInstance;

//////////////////////////////////////////////////////////////////////////////
// class OnDemandSingleton <T> declaration

// purpose: this is a Singleton that is instantiated on demand and destroyed
//          automatically at app shutdown. do not instantiate 'T' manually.
//          this is a "traditional" singleton class that you see in textbooks.

template <typename T>
T& GetOnDemandSingleton( void )
{
	static T s_Singleton;
	return ( s_Singleton );
}

template <typename T>
class OnDemandSingleton
{
protected:
	OnDemandSingleton( void )
	{
		assert( !ms_SingletonExists );
		ms_SingletonExists = true;
	}
   ~OnDemandSingleton( void )
	{
		assert( ms_SingletonExists );
		ms_SingletonExists = false;
	}

public:
	static T&   GetSingleton      ( void )	{  return ( GetOnDemandSingleton <T> () );  }
	static T*   GetSingletonPtr   ( void )  {  return ( &GetSingleton() );  }
	static bool DoesSingletonExist( void )  {  return ( ms_SingletonExists );  }

private:
	static bool ms_SingletonExists;
};

template <typename T>
bool OnDemandSingleton <T>::ms_SingletonExists = false;

//////////////////////////////////////////////////////////////////////////////

#endif  // __DSDLL_H

//////////////////////////////////////////////////////////////////////////////
