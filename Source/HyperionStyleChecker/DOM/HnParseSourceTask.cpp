/// LLVM & CLANG includes should go first,
/// cause including STL headers first may cause trouble.
#include <ThirdParty\clang\include\llvm/Support/Host.h>
#include <ThirdParty\clang\include\llvm/ADT/IntrusiveRefCntPtr.h>

#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Parse/Parser.h>
#include <clang/Parse/ParseAST.h>

#include <HyperionStyleChecker/DOM/HnParseSourceTask.h>

//http://clang.llvm.org/docs/RAVFrontendAction.html
//https://github.com/hdpatel/systemc-clang/tree/revamp/src
//http://clang.llvm.org/doxygen/classclang_1_1CXXRecordDecl.html

//CXXRecordDecl
//field_begin and field_end
//method_begin and method_end

using namespace clang;

/*namespace HyperionStyleChecker
{
	class HnFindNamedClassVisitor : public RecursiveASTVisitor<HnFindNamedClassVisitor>
	{
	public:
		HnParsedFile * pParsedFile;

		HnFindNamedClassVisitor(ASTContext * pContext)
		{
		}

		bool VisitCXXRecordDecl(CXXRecordDecl *Declaration)
		{
			return true;
		}

		bool VisitDecl(Decl * pDeclaration)
		{
			HnClassDef classDef;

			return true;
		}
	};

	class HnASTConsumer : public ASTConsumer
	{
	public:
		HnParsedFile * pParsedFile;

		HnASTConsumer()
			: ASTConsumer()
		{
		}
		
		virtual void HandleTranslationUnit(ASTContext & rContext)
		{
			HnFindNamedClassVisitor visitor(&rContext);
			visitor.pParsedFile = pParsedFile;

			visitor.TraverseDecl(rContext.getTranslationUnitDecl());
		}

	protected:
	};

	HnParseSourceTask::HnParseSourceTask()
	{
		_pParsedFile = HnNullPointer;
	}

	HnParseSourceTask::HnParseSourceTask(const HnString & crSourceFilePath, HnParsedFile * pParsedFile)
	{
		_sSourceFilePath = crSourceFilePath;

		_pParsedFile = pParsedFile;
		_pParsedFile->sFilePath = crSourceFilePath;
	}
	
	HnParseSourceTask::~HnParseSourceTask()
	{
	}

	void HnParseSourceTask::operator()() const
	{
		using clang::CompilerInstance;
		using clang::TargetOptions;
		using clang::TargetInfo;
		using clang::FileEntry;
		using clang::Token;
		using clang::ASTContext;
		using clang::ASTConsumer;
		using clang::Parser;
		using clang::DiagnosticOptions;
		using clang::TextDiagnosticPrinter;

		CompilerInstance ci;
		DiagnosticOptions diagnosticOptions;
		TextDiagnosticPrinter *pTextDiagnosticPrinter =
			new TextDiagnosticPrinter(
				llvm::outs(),
				&diagnosticOptions,
				true);
		ci.createDiagnostics(pTextDiagnosticPrinter);

		llvm::IntrusiveRefCntPtr<TargetOptions> pto(new TargetOptions());
		pto->Triple = llvm::sys::getDefaultTargetTriple();
		TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), pto.getPtr());
		ci.setTarget(pti);

		ci.createFileManager();
		ci.createSourceManager(ci.getFileManager());
		ci.createPreprocessor();
		ci.getPreprocessorOpts().UsePredefines = false;

		HnASTConsumer * pAstConsumer = new HnASTConsumer();
		pAstConsumer->pParsedFile = const_cast<HnParsedFile *>(_pParsedFile);

		ci.setASTConsumer(pAstConsumer);
		ci.createASTContext();

		const FileEntry *pFile = ci.getFileManager().getFile(_sSourceFilePath.c_str());
		ci.getSourceManager().createMainFileID(pFile);
		ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), &ci.getPreprocessor());
		ParseAST(ci.getPreprocessor(), pAstConsumer, ci.getASTContext());
		ci.getDiagnosticClient().EndSourceFile();
	}
}*/

namespace HyperionStyleChecker
{
	class HnClassDefASTConsumer : public clang::ASTConsumer
	{
	public:
		HnClassDefASTConsumer() : clang::ASTConsumer(), _pParsedFile(HnNullPointer) { }

		HnClassDefASTConsumer(const HnClassDefASTConsumer& crHnClassDefASTConsumer) 
			: clang::ASTConsumer()
		{
			*this = crHnClassDefASTConsumer;
		}

		virtual ~HnClassDefASTConsumer() { }

		virtual bool HandleTopLevelDecl( clang::DeclGroupRef d)
		{
			static int count = 0;
			clang::DeclGroupRef::iterator it;
			for( it = d.begin(); it != d.end(); it++)
			{
				count++;
				clang::VarDecl *vd = llvm::dyn_cast<clang::VarDecl>(*it);
				if(!vd)
				{
					continue;
				}
				if( vd->isFileVarDecl() && !vd->hasExternalStorage() )
				{
					HnClassDef classDef;
					classDef.sClassName = vd->getDeclName().getAsString();
					_pParsedFile->classDefs.push_back(classDef);
				}
			}
			return true;
		}

		void SetParsedFile(HnParsedFile * pParsedFile)
		{
			_pParsedFile = pParsedFile;
		}

		HnClassDefASTConsumer& operator=(const HnClassDefASTConsumer& crHnClassDefASTConsumer)
		{
			_pParsedFile = crHnClassDefASTConsumer._pParsedFile;

			return *this;
		}
	protected:
		HnParsedFile * _pParsedFile;
	};

	HnParseSourceTask::HnParseSourceTask()
	{
		_pParsedFile = HnNullPointer;
	}

	HnParseSourceTask::HnParseSourceTask(const HnString & crSourceFilePath, HnParsedFile * pParsedFile)
	{
		_sSourceFilePath = crSourceFilePath;

		_pParsedFile = pParsedFile;
		_pParsedFile->sFilePath = crSourceFilePath;
	}
	
	HnParseSourceTask::~HnParseSourceTask()
	{
	}

	void HnParseSourceTask::operator()() const
	{
		using clang::CompilerInstance;
		using clang::TargetOptions;
		using clang::TargetInfo;
		using clang::FileEntry;
		using clang::Token;
		using clang::ASTContext;
		using clang::ASTConsumer;
		using clang::Parser;
		using clang::DiagnosticOptions;
		using clang::TextDiagnosticPrinter;

		CompilerInstance ci;
		DiagnosticOptions diagnosticOptions;
		TextDiagnosticPrinter *pTextDiagnosticPrinter =
			new TextDiagnosticPrinter(
				llvm::outs(),
				&diagnosticOptions,
				true);
		ci.createDiagnostics(pTextDiagnosticPrinter);

		std::shared_ptr<TargetOptions> pto(new TargetOptions());
		pto->Triple = llvm::sys::getDefaultTargetTriple();
		TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), pto);
		ci.setTarget(pti);

		ci.createFileManager();
		ci.createSourceManager(ci.getFileManager());
		ci.createPreprocessor(clang::TU_Complete);
		ci.getPreprocessorOpts().UsePredefines = false;

		std::unique_ptr<ASTConsumer> astConsumer(new HnClassDefASTConsumer());
		/////////////////////////////////////astConsumer->SetParsedFile(const_cast<HnParsedFile *>(_pParsedFile));

		ci.setASTConsumer(std::unique_ptr<HnClassDefASTConsumer>());

		ci.createASTContext();

		const FileEntry *pFile = ci.getFileManager().getFile(_sSourceFilePath.c_str());
		ci.getSourceManager().createFileID(pFile, SourceLocation(), SrcMgr::C_User);
		ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(),
												 &ci.getPreprocessor());
		clang::ParseAST(ci.getPreprocessor(), astConsumer.get(), ci.getASTContext());
		ci.getDiagnosticClient().EndSourceFile();
	}
}