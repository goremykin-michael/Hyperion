#pragma once

#include <string>
#include <vector>

using namespace std;

namespace HyperionStyleChecker
{
	enum SymbolEnum
	{
		TAB,
		SPACE
	};
	struct BlockPosition
	{
		int row;
		int column;
	};
	class ASTNode;
	class Text
	{
	public:
		static string Format(const string& format, ...) { return string(); }
	};
	class Block
	{
	public:
		BlockPosition GetLeftUpperPosition()     { return BlockPosition(); }
		BlockPosition GetRightBottomPosition()   { return BlockPosition(); }
		int GetHeight()			 { return 0; }
		int GetWidth()			 { return 0; }
	};
	class Symbols
	{
	public:
		bool ContainsSymbol(SymbolEnum symbol) { return true; }
		int Length() { return 0; }
	};

	class Atom
	{
	public:
		template <class ASTNode> ASTNode AST() { return ASTNode(); }
		Block block;
		Symbols symbols;

	};

	class ASTNode : public Atom
	{

	};
	class FunctionCall : public ASTNode
	{
	public:
		vector<Atom> GetParameters() { return vector<Atom>(); }
		string GetName() { return string(); }
	};
	class AST
	{
	public:
		vector<Atom> GetAncestors() { return vector<Atom>(); }
		bool IsInterface()				  { return true; }
		string GetName()				  { return string(); }


	};

	class Source
	{
	public:
		vector<Atom> GetFunctions() const { return vector<Atom>(); }
		
		vector<Atom> GetFunctionCalls() const { return vector<Atom>(); }
		vector<Atom> GetBlocks() const    { return vector<Atom>(); }
		vector<Atom> GetClasses()const    { return vector<Atom>(); }
		string GetName()const         { return string(); }

	};
}