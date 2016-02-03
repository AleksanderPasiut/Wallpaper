#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

void RetrieveFileNames(vector<wstring>& file_list)
{
	wstring files_path = L"C:\\Users\\Avert Second\\Pictures\\wot\\*";

	WIN32_FIND_DATA data;
	HANDLE hFound = FindFirstFile(files_path.c_str(), &data);
	files_path.erase(--files_path.end());
	do
	{
		wstring w = data.cFileName;

		if (w != L"." && w != L"..")
			file_list.push_back(files_path+w);
	}
	while (FindNextFile(hFound, &data));
}

void SetRandomDesktopWallpaper(vector<wstring>& file_list)
{
	srand(GetTickCount());
	int index = rand()%file_list.size();
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, const_cast<wchar_t*>(file_list[index].c_str()), SPIF_UPDATEINIFILE);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	vector<wstring> file_list;

	RetrieveFileNames(file_list);

	SetRandomDesktopWallpaper(file_list);

	return 0;
}