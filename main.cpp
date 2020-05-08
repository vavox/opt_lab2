
#include "main.h"
#include "syntax.h"

int main()
{
    
    string test;
    cout << "Enter folder (TrueTest(1-4) or FalseTest(1-10)): " << endl;
    cin >> test;
    ifstream fin("Test/" + test + "/input.sig");
    ofstream fout1("Test/" + test + "/generated.txt");
    ofstream fout2("Test/" + test + "/expected.txt");
    ofstream fout3("Test/" + test + "/generated_tree.txt");
    if (fin.peek() == std::ifstream::traits_type::eof()) 
    {
        cout << "Empty file or no file" << endl;
        return 0;
    }

    lexer(fin);

   
    show(fout1, fout2);
    
    if(!Parser())
    {
       show_error();
    }
    
    
    cout << endl << "Tree:" << endl << endl;
    fout3 << "Tree:" << endl << endl;
    print_tree("", tree, false, fout3);
    
    fin.close();
    fout1.close();
    fout2.close();
    fout3.close();
    return 0;
}