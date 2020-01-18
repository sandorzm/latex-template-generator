#include <fstream>
#include <iostream>
#include <string>

// Writes a problem template described in p to out
void print_problem(std::ofstream &out, const std::string &p) {

	out << "\\section*{Problem ";   // Create document section
	unsigned i = 0;
	for (; i < p.size() && p[i] != '('; ++i); // Find first "(" or end of string
	out << p.substr(0, i) << "}\n"; // Write problem number

	if (i == p.size())              // No problem parts specified
		return;

	out << "\\begin{enumerate}\n";  // Make list of problem parts
	++i;                            // Advance to first part identifier
	while (i < p.size()) {          // Loops once per part
		unsigned j = 0;
		for (; i+j < p.size() && p[i+j] != '('; ++j); // Find next "(" or end of string
		out << "\t\\item[" << p.substr(i, j) << "]\n"; // Write part identifier
		i += j+1;                   // Advance to next part description
	}
	out << "\\end{enumerate}\n";
}

int main() {

	// Ask for output file and create file stream
	std::string temp;
	std::cout << "Output file: "; // e.g. hw5.tex
	std::cin >> temp;
	std::ofstream out(temp);
	if (!out.good()) {
		std::cerr << "Couldn't open " << temp << '.' << std::endl;
		return 1;
	}

	// Ask for name and course and print document frontmatter
	std::cout << "Your name: ";
	std::getline(std::cin, temp);
	std::getline(std::cin, temp);
	out << "\\documentclass{article}\n"
		"\\usepackage{amsmath}\n"
		"\\usepackage{amssymb}\n"
		"\\usepackage{graphicx}\n\n"
		"\\begin{document}\n"
		"\\noindent\n"
		"\\parbox{0.3\\textwidth}{" << temp <<
		"}\\parbox{0.4\\textwidth}{\\centering ";
	std::cout << "Course name: ";
	std::getline(std::cin, temp);
	out << temp << "}\\parbox{0.3\\textwidth}{\\raggedleft ";

	// Print date and assignment number
	std::cout << "Date: ";
	std::getline(std::cin, temp);
	out << temp << "}\n\n"
		"\\vspace{4mm}\n"
		"\\noindent\n"
		"\\begin{center}\n"
		"{\\LARGE ";

	std::cout << "Assignment name: ";
	std::getline(std::cin, temp);
	out << temp << "}\n\\end{center}\n\n";

	// Get number of problems and each problem string
	unsigned problems = 0;
	std::cout << "Number of problems: ";
	std::cin >> problems;
	std::cout << "Enter problems like \"9.3(b)(e)\".\n";
	for (unsigned i = 0; i < problems; ++i) {
		std::cout << i+1 << ": ";
		std::cin >> temp;         // Get problem string
		print_problem(out, temp); // Write problem to file
		if (i != problems-1)
			out << "\\newpage\n"; // Every problem starts on a new page
	}
	out << "\\end{document}";
	std::cout << "Finished writing." << std::endl;
	return 0;
}