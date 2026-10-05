// include the 2d game header file
#include "glc2d.h"
#include "CApplication.h"


int main()
{
	g_app.Init();

	// ½ÇÇà
	g2_Run();

	g_app.Destroy();

	return 0;
}