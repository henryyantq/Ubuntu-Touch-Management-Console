#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void adb_shell(char *cmd) {
	char shell[200] = "adb shell ";
	system(strcat(shell, cmd));
}

void cd(char *root) {
	char cmd[200] = "cd ";
	adb_shell(strcat(cmd, root));
}

void file_push(char *start, char *end) {
	char push[500] = "adb push ";
	strcat(push, start);
	strcat(push, " ");
	system(strcat(push, end));
}

void file_pull(char *start, char *end) {
	char pull[500] = "adb pull ";
	strcat(pull, start);
	strcat(pull, " ");
	system(strcat(pull, end));
}

void lapse(double dur) {
	time_t start, end;
	start = clock();
	end = start;
	while (1) {
		if ((end - start) / CLOCKS_PER_SEC == dur) break;
		end = clock();
	}
}

void apk_inst(char *filepath) {
	char inst[500] = "adb install ";
	adb_shell(strcat(inst, filepath));
}

int main() {
	int choice;
	lapse(1);
	cout << endl << "Ubuntu Touch Management Console\n";
	lapse(1);
	cout << endl << "Made by Henry Yan (@Evergardener)" << endl << endl;
	lapse(1);
	cout << "Have you already deployed ADB on your computer?\n1. Yes.\n2. No.\n--> ";
	cin >> choice;
	if (choice == 2) {
		cout << "Sorry, please deploy ADB (Android Debug Bridge) on your computer first.\n";
		exit(0);
	}
	cout << endl << "Initializing ADB tunnel...\n\n";
	system("adb kill-server");
	system("adb start-server");
	while (1) {
		system("adb devices");
		cout << "Is your Ubuntu Touch device correctly identified?\n1. Yes.\n2. Try again.\n--> ";
		cin >> choice;
		if (choice == 1) break;
		else cout << endl;
	}
	lapse(1);
	cout << endl;
	while (1) {
		char filepath1[200];
		char filepath2[200];
		cout << "Menu:\n1. Read storage status of your UT device\n";
		cout << "2. Copy file(s) to your device\n3. Copy file(s) from...\n4. Install APK(s) (Anbox required)\n5. Uninstall APK(s)\n";
		cout << "6. Export photo albums\n7. Remount main storage as read-and-write\n8. Reboot to bootloader (Fastboot mode)\n9. Shutdown (Forced)\n10. Reboot (Forced)\n";
		cout << "11. Reboot and factory reset\n12. Reboot to Ubuntu Touch from bootloader (Fastboot mode)\n13. Reboot to recovery from bootloader (Fastboot mode)\n14. Flash third-party recovery in bootloader (Fastboot mode)\n15. Ubuntu Touch terminal\n16. Reconnect your device\n17. Serial no. of your device" << endl << "--> ";
		cin >> choice;
		cout << endl;
		if (choice == 1) {
			adb_shell("df -H");
			cout << endl;
		}	//选项1
		else if (choice == 2) {
			cout << "Path of local file (drag to here): ";
			cin >> filepath1;
			cout << "Path of device's target directory\n1. Main directory\n2. Documents\n3. Downloads\n4. Music\n5. Pictures\n6. Videos\n--> ";
			cin >> choice;
			if (choice == 1)
				file_push(filepath1, "/home/phablet");
			else if (choice == 2)
				file_push(filepath1, "/home/phablet/Documents");
			else if (choice == 3)
				file_push(filepath1, "/home/phablet/Downloads");
			else if (choice == 4)
				file_push(filepath1, "/home/phablet/Music");
			else if (choice == 5)
				file_push(filepath1, "/home/phablet/Pictures");
			else if (choice == 6)
				file_push(filepath1, "/home/phablet/Videos");
			cout << endl;
		}	//选项2
		else if (choice == 3) {
			cout << "Path of file to be copied from your device: ";
			cin >> filepath2;
			cout << "Path of target local directory (drag to here): ";
			cin >> filepath1;
			file_pull(filepath2, filepath1);
			cout << endl;
		}	//选项3
		else if (choice == 4) {
			char save_path[300] = "/home/phablet/Downloads";
			char *apk_name;
			int count = 0;
			int flag;
			cout << "Path of the local APK to be installed on your device: ";
			cin >> filepath1;
			file_push(filepath1, save_path);
			for (int i = 0; i < 500; i++) {
				if (filepath1[i] == '.' && filepath1[i + 1] == 'a' && filepath1[i + 2] == 'p' && filepath1[i + 3] == 'k') {
					for (int k = i + 3; k > 0; k--) {
						count++;
						if (filepath1[k] == '\\') {
							flag = k;
							break;
						}
					}
					break;
				}	//找到 .apk 字样
			}	//得到 apk 文件名
			apk_name = new char[count];
			apk_name[count - 1] = '\0';
			for (int i = flag + 1, k = 0, calc = 0; calc < count; calc++, i++, k++) {
				apk_name[k] = filepath1[i];
			}	//得到 apk 文件名
			cout << "APK filename: " << apk_name << endl;
			strcat(save_path, "/");
			strcat(save_path, apk_name);
			apk_inst(save_path);
			cout << endl;
		}	//选项4
		else if (choice == 5) {
			char package[200];
			char uninst[500] = "adb uninstall ";
			cout << "List of APKs installed:" << endl;
			adb_shell("adb shell pm list packages");
			cout << endl << "The package name of the app to be removed: ";
			cin >> package;
			adb_shell(strcat(uninst, package));
			cout << endl;
		}	//选项5
		else if (choice == 6) {
			cout << "Path of target local directory (drag to here): ";
			cin >> filepath1;
			file_pull("/home/phablet/Pictures", filepath1);
			cout << endl;
		}
		else if (choice == 7) {
			cout << "Please input lockscreen (admin) password below.\n";
			adb_shell("sudo mount -o remount,rw /");
		}
		else if (choice == 8) {
			system("adb reboot bootloader");
		}
		else if (choice == 9) {
			cout << "Please input lockscreen (admin) password below.\n";
			system("adb shell sudo poweroff");
		}
		else if (choice == 10) {
			system("adb reboot");
		}
		else if (choice == 11) {
			system("adb reboot bootloader");
			system("fastboot format cache");
			system("fastboot format userdata");
			system("fastboot reboot");
		}
		else if (choice == 12) {
			system("fastboot reboot");
			cout << endl;
		}
		else if (choice == 13) {
			system("fastboot reboot recovery");
			cout << endl;
		}
		else if (choice == 14) {
			cout << "Path of the local recovery file (.img) (drag to here)：";
			cin >> filepath1;
			cout << "Make sure your Ubuntu Touch device is in bootloader (Fastboot mode)!\n";
			char str[500] = "fastboot flash recovery ";
			system(strcat(str, filepath1));
		}
		else if (choice == 15) {
			system("adb shell");
			cout << endl;
		}
		else if (choice == 16) {
			system("adb reconnect");
			system("adb devices");
		}
		else if (choice == 17) {
			cout << "The serial no. of your device is ";
			system("adb get-serialno");
			cout << endl;
		}
	}	//功能列表循环
}
