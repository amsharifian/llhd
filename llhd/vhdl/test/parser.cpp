/* Copyright (c) 2014 Fabian Schuiki */
#include <llhd/SourceBuffer.hpp>
#include <llhd/SourceLocation.hpp>
#include <llhd/vhdl/LexerNovum.hpp>
#include <llhd/vhdl/Parser.hpp>
#include <llhd/vhdl/TokenContext.hpp>
#include <llhd/vhdl/ast/Context.hpp>
#include <iostream>
#include <fstream>


int main(int argc, char** argv)
{
	try {

		// Make sure we have enough arguments.
		if (argc < 2) {
			std::cerr << "no input files\n";
			std::cerr << "usage: " << argv[0] << " filename ...\n";
			return 1;
		}

		// Lex all the source files.
		llhd::vhdl::TokenContext ctx;
		llhd::vhdl::LexerNovum lexer(ctx);
		std::cout << "starting to lex things\n";
		for (int i = 1; i < argc; i++) {
			std::cout << "opening " << argv[i] << "... ";
			std::ifstream fin(argv[i]);
			fin.seekg(0, std::ios_base::end);
			size_t length = fin.tellg();
			fin.seekg(0, std::ios_base::beg);
			std::cout << "done (" << length << " bytes)\n";
			char data[length+1];
			fin.read(data, length);
			data[length] = 0;
			lexer.lex(llhd::SourceBuffer(data, data+length+1), llhd::SourceLocation());
		}

		// Create an instance of the parser and feed it each file sequentially.
		// llhd::vhdl::Parser parser;
		// for (int i = 1; i < argc; i++) {
		// 	std::ifstream fin(argv[i]);
		// 	parser.parse(fin);
		// }

		// llhd::vhdl::ast::Context ctx;
		// ctx.alloc.allocate(128);

	} catch (std::exception& e) {
		std::cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
