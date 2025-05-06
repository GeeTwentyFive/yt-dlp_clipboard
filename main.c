#include <Windows.h>



char command[8191] = "yt-dlp ";



int main() {

        OpenClipboard(NULL);

        HANDLE hData = GetClipboardData(CF_TEXT);

        GlobalLock(hData);



        char* data = (char*)hData;



        // Input sanitization:

        if (strlen(data)+strlen(command) > sizeof(command)) {
                system("echo ERROR: Clipboard contents too large!");
                system("pause");
                return 1;
        }

        for (int i = 0; i < strlen(data); i++)
                if (!(
                        (data[i] >= '0' && data[i] <= '9') ||
                        (data[i] >= 'a' && data[i] <= 'z') ||
                        (data[i] >= 'A' && data[i] <= 'Z') ||
                        data[i] == '.' ||
                        data[i] == '/' ||
                        data[i] == ':' ||
                        data[i] == '?' ||
                        data[i] == '='
                )) {
                        system("echo ERROR: Unallowed character in clipboard contents!");
                        system("pause");
                        return 2;
                }



        strcat(command, data);
        system(command);
        system("pause");



        GlobalUnlock(hData);

        CloseClipboard();

        return 0;

}