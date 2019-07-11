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
	cout << endl << "Ubuntu Touch 设备管理\n";
	lapse(1);
	cout << endl << "由 Henry Yan (@Evergardener) 制作" << endl << endl;
	lapse(1);
	cout << "您的设备是否安装了 adb 文件？\n1、是的\n2、否，请为我安装（仅限 Mac OS X）\n--> ";
	cin >> choice;
	if (choice == 2)
		system("brew cask install android-platform-tools");
	cout << endl << "正在初始化 ADB 服务端...\n\n";
	system("adb kill-server");
	system("adb start-server");
	while (1) {
		system("adb devices");
		cout << "您的 Ubuntu Touch 设备是否被识别正确？\n1、是的\n2、再试一次\n--> ";
		cin >> choice;
		if (choice == 1) break;
		else cout << endl;
	}
	lapse(1);
	cout << endl;
	while (1) {
		char filepath1[200];
		char filepath2[200];
		cout << "功能列表：\n1. 查看设备的存储容量状态\n";
		cout << "2. 复制本地文件到设备指定目录\n3. 复制设备文件到本地指定目录\n4. 安装 Android 包到设备（须已部署 Anbox）\n5. 卸载 Android 应用程序\n";
		cout << "6. 导出设备相册\n7. 重载存储系统可读写\n8. 重启设备至刷机模式\n9. 强制关机\n10. 强制重新启动\n";
		cout << "11. 重新启动并还原出厂设置\n12. 从刷机模式重启至 Ubuntu Touch\n13. 从刷机模式重启至 Recovery\n14. 从刷机模式刷入非官方 Recovery\n15. 访问设备终端\n16. 重新连接设备\n17. 获取设备序列号" << endl << "--> ";
		cin >> choice;
		cout << endl;
		if (choice == 1) {
			adb_shell("df -H");
			cout << endl;
		}	//选项1
		else if (choice == 2) {
			cout << "本地文件路径：";
			cin >> filepath1;
			cout << "设备目标目录路径选择：\n1. 主目录\n2. Documents\n3. Downloads\n4. Music\n5. Pictures\n6. Videos\n--> ";
			cin >> choice;
			if (choice == 1)
				file_push(filepath1, "/home/phablet");
			else if (choice == 2)
				file_push(filepath1, "/home/phablet/Documents");
			else if (choice == 3)
				file_push(filepath1, "/home/phablet/Downloads");
			else if (choice == 4)
				file_push(filepath1, "home/phablet/Music");
			else if (choice == 5)
				file_push(filepath1, "/home/phablet/Pictures");
			else if (choice == 6)
				file_push(filepath1, "/home/phablet/Videos");
			cout << endl;
		}	//选项2
		else if (choice == 3) {
			cout << "设备文件路径：";
			cin >> filepath2;
			cout << "本地目标目录路径：";
			cin >> filepath1;
			file_pull(filepath2, filepath1);
			cout << endl;
		}	//选项3
		else if (choice == 4) {
			char save_path[300] = "/home/phablet/Downloads";
			char *apk_name;
			int count = 0;
			int flag;
			cout << "本地安卓文件路径：";
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
			cout << "APK 文件名：" << apk_name << endl;
			strcat(save_path, "/");
			strcat(save_path, apk_name);
			apk_inst(save_path);
			cout << endl;
		}	//选项4
		else if (choice == 5) {
			char package[200];
			char uninst[500] = "adb uninstall ";
			cout << "APK 包列表如下：" << endl;
			adb_shell("adb shell pm list packages");
			cout << endl << "请输入对应包名以卸载 Android 应用程序：";
			cin >> package;
			adb_shell(strcat(uninst, package));
			cout << endl;
		}	//选项5
		else if (choice == 6) {
			cout << "请输入本地目标目录路径：";
			cin >> filepath1;
			file_pull("/home/phablet/Pictures", filepath1);
			cout << endl;
		}
		else if (choice == 7) {
			cout << "输入管理员（超级用户权限）密码以完成操作\n";
			adb_shell("sudo mount -o remount,rw /");
		}
		else if (choice == 8) {
			system("adb reboot bootloader");
		}
		else if (choice == 9) {
			cout << "输入管理员（超级用户权限）密码以完成操作\n";
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
			cout << "请输入 Recovery 镜像文件路径：";
			cin >> filepath1;
			cout << "确保您的 Ubuntu Touch 设备已进入刷机模式（Fastboot）！\n";
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
			cout << "您的设备序列号为：";
			system("adb get-serialno");
			cout << endl;
		}
	}	//功能列表循环
}
