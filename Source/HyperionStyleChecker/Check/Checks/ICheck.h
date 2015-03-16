#pragma once
#include <HyperionStyleChecker/DOM/Source.h>
#include <HyperionStyleChecker/Check/CheckResult.h>

namespace HyperionStyleChecker
{
	class ICheck
	{
	public:
		virtual ~ICheck() {}

		virtual CheckResult Check(const Source & crSource) = 0;
	};

	//class LineCharacterLengthCheck : ICheck
	//{
	//public:
	//	CheckResult Check(const Source * cpSource)
	//	{
	//		CheckResult checkResult;

	//		for each(Atom atom in cpSource->GetBlocks())
	//		{
	//			if (atom.Block.GetWidth() > 100)
	//			{
	//				checkResult.sWhat.append("[" + cpSource->GetSourceFileName() + "] "
	//					                     "The line " + to_string(atom.Block.GetStartCoordinate()) 
	//										 + "is too long.");
	//			}
	//		}

	//		return checkResult;
	//	}
	//};

	//class MultipleInheritanceCheck : ICheck
	//{
	//public:
	//	CheckResult Check(const Source * cpSource)
	//	{
	//		CheckResult checkResult;

	//		int iCountOfAncestors = 0;

	//		for each (Atom atom in cpSource->GetClasses())
	//		{
	//			for each (Atom subAtom in atom.AST.GetAncestors())
	//			{
	//				if (!subAtom.AST.IsInterface())
	//				{
	//					++iCountOfAncestors;
	//				}
	//			}

	//			if (iCountOfAncestors > 1)
	//			{
	//				checkResult.sWhat.append("Class" + atom.AST.GetName() + "in file" +
	//					cpSource->GetSourceFileName() + "has too many ancestors.");
	//			}

	//			iCountOfAncestors = 0;
	//		}

	//		return checkResult;
	//	}
	//};

	//class IdenationFormattingCheck : ICheck
	//{
	//public:
	//	CheckResult Check(const Source * cpSource)
	//	{
	//		CheckResult checkResult;

	//		for each (Atom atom in cpSource->GetBlocks())
	//		{
	//			if (atom.Symbols.ContainsSymbol(TAB))
	//			{
	//				checkResult.sWhat.append("Line" + to_string(atom.Block.GetStartCoordinate())
	//					+ "contains \"tab\" symbol");
	//			}
	//		}

	//		return checkResult;
	//	}
	//};
	
	class FunctionCallLengthCheck : ICheck
	{
	public:
		CheckResult Check(const Source & crSource) override
		{
			CheckResult checkResult;

			for each (Atom atom in crSource.GetFunctionCalls())
			{
				vector<Atom> functionParameters = atom.AST<FunctionCall>().GetParameters();

				if (functionParameters.size() > 1 &&
					(functionParameters[0].block.GetLeftUpperPosition().row ==
					functionParameters[functionParameters.size() - 1].block.GetRightBottomPosition().row))
				{
					unsigned int uiFunctionCallLength = 0;

					for each(Atom parameterAtom in functionParameters)
					{
						uiFunctionCallLength += parameterAtom.symbols.Length();
					}

					if (uiFunctionCallLength > _uiMaxFunctionCallLength)
					{
						checkResult.sWhat.append(Text::Format("Строка с вызовом функции {0} слишком длинная ({1}:{2}).\n",
								                              atom.AST<FunctionCall>().GetName(),
															  crSource.GetName(),
															  atom.block.GetLeftUpperPosition().row));
					}
				}
			}

			return checkResult;
		}

	private:
		const unsigned int _uiMaxFunctionCallLength = 150;
	};
}