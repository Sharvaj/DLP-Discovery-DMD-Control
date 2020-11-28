
# include "MyHeaders.h"
// # include other stuff


void myCheckRowModes() {
	using namespace std;
	short RowMode = USB::GetRowMd(0);

	cout << "The row mode is: " << RowMode << endl;

}