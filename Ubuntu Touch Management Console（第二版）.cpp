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

void create_lib(char *id, char *name) {
	cout << "正在创建 Libertine 容器 " << name << " 。需要一段时间，请勿关闭程序..." << endl;
	char create[200] = "libertine-container-manager create -i ";
	strcat(create, id);
	strcat(create, " -n ");
	strcat(create, "'");
	strcat(create, name);
	adb_shell(strcat(create, "'"));
}

void libertine(char *id, char *cmd) {
	char lib[200] = "libertine-container-manager ";
	strcat(lib, cmd);
	strcat(lib, " -i ");
	adb_shell(strcat(lib,id));
}

void inst_pkg(char *id, char *pkg_name) {
	cout << "正在安装桌面应用程序包 " << pkg_name << " 。需要一段时间，请勿关闭程序..." << endl;
	char lib[200] = "libertine-container-manager install-package -i ";
	strcat(lib, id);
	strcat(lib, " -p ");
	adb_shell(strcat(lib, pkg_name));
}	//Libertine 操作

void uninst_pkg(char *id, char *pkg_name) {
	cout << "正在移除桌面应用程序包 " << pkg_name << " 。需要一段时间，请勿关闭程序..." << endl;
	char lib[200] = "libertine-container-manager remove-package -i ";
	strcat(lib, id);
	strcat(lib, " -p ");
	adb_shell(strcat(lib, pkg_name));
}	//Libertine 操作

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
	cout << "您的设备是否安装了 ADB 调试环境？\n1、是的\n2、否\n--> ";
	cin >> choice;
	if (choice == 2) {
		cout << "对不起，请您部署完成 ADB 调试环境后再运行本程序。";
		exit(0);
	}
	cout << endl << "正在初始化 ADB 服务端...\n\n";
	system("adb kill-server");
	system("adb start-server");
	while (1) {
		system("adb devices");
		cout << "您的 Ubuntu Touch 设备是否被识别正确？\n1、是的\n2、再试一次\n3、我的设备处于刷机模式\n--> ";
		cin >> choice;
		cin.get();
		if (choice == 1 || choice == 3) break;
		else cout << endl;
	}
	if (choice == 1) {
		lapse(1);
		cout << endl;
	}
	else if (choice == 3) {
		cout << endl << "是否从刷机模式重启至 Ubuntu Touch?\n1、好的\n2、出了些问题，直接进入功能列表\n--> ";
		cin >> choice;
		cin.get();
		if (choice == 1) {
			cout << endl;
			system("fastboot reboot");
		}
	}
	cout << endl;
	while (1) {
		char filepath1[200];
		char filepath2[200];
		strcpy(filepath1, "");
		strcpy(filepath2, "");
		cout << "功能列表：\n1. 查看设备的存储容量状态\n";
		cout << "2. 复制本地文件到设备指定目录\n3. 复制设备文件到本地指定目录\n4. 安装 Android 包到设备（须已部署 Anbox）\n5. 卸载 Android 应用程序\n6. Libertine 桌面应用程序容器\n";
		cout << "7. 导出设备相册\n8. 重载存储系统可读写\n9. 重启设备至刷机模式\n10. 强制关机\n11. 强制重新启动\n";
		cout << "12. 重新启动并还原出厂设置\n13. 从刷机模式重启至 Ubuntu Touch\n14. 从刷机模式重启至 Recovery\n15. 从刷机模式刷入非官方 Recovery\n16. 访问设备终端\n17. 重新连接设备\n18. 获取设备序列号" << endl << "--> ";
		cin >> choice;
		cin.get();
		cout << endl;
		if (choice == 1) {
			adb_shell("df -H");
			cout << endl;
		}	//选项1
		else if (choice == 2) {
			cout << "本地文件路径：";
			cin.getline(filepath1, 200);
			cout << endl;
			cout << "设备目标目录路径选择：\n1. 主目录\n2. Documents\n3. Downloads\n4. Music\n5. Pictures\n6. Videos\n--> ";
			cin >> choice;
			cin.get();
			cout << endl;
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
			cout << "设备文件路径：";
			cin.getline(filepath2, 200);
			cout << "本地目标目录路径：";
			cin.getline(filepath1, 200);
			file_pull(filepath2, filepath1);
			cout << endl;
		}	//选项3
		else if (choice == 4) {
			char save_path[300] = "/home/phablet/Downloads";
			char *apk_name;
			int count = 0;
			int flag;
			cout << "本地安卓文件路径：";
			cin.getline(filepath1, 200);
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
			cin.getline(package, 200);
			adb_shell(strcat(uninst, package));
			cout << endl;
		}	//选项5
		else if (choice == 6) {
			char lib_id[50];
			char lib_name[50];
			cout << "Libertain 容器管理\n\n";
			lapse(1);
			cout << "1. 部署一个全新的 Libertine\n2. 管理现有的 Libertine 容器\n3. 离开 Libertine 容器管理\n--> ";
			cin >> choice;
			cin.get();
			cout << endl;
			if (choice == 1) {
				cout << "需要进行一些设置。\n可能需要您输入管理员（超级用户权限）密码!\n";
				adb_shell("sudo apt-get install python3-libertine-chroot");
				cout << "设置完毕。\n\n为您即将部署的 Libertine 容器设置一个 ID（仅可包含小写字母）：";
				cin.getline(lib_id, 50);
				cout << "现在请您为容器设置一个名称（不能包含汉字或特殊符号）：";
				cin.getline(lib_name, 50);
				create_lib(lib_id, lib_name);
				cout << "创建完成！\n创建成功以下 Libertine 容器：" << endl;
				adb_shell("libertine-container-manager list");
				cout << endl;
				goto choice_2;
			}
			else if (choice == 2) {
			choice_2:
				while (1) {
					char  id[50];
					strcpy(id, "");
					cout << "Libertine 操作一览：" << endl;
					cout << "1. 查看已部署的 Libertine 容器 ID\n2. 查看已安装的 X11 桌面应用程序\n3. 安装一个 X11 桌面应用程序\n4. 移除一个 X11 桌面应用程序\n5. 离开 Libertine 容器管理\n--> ";
					cin >> choice;
					cin.get();
					cout << endl;
					if (choice == 5) break;
					else if (choice == 1) {
						cout << "目前的容器包括：" << endl;
						adb_shell("libertine-container-manager list");
					}	//Libertine 操作 - 1
					else if (choice == 2) {
						cout << "请输入您需要查看的容器 ID：";
						cin.getline(id, 50);
						cout << "该容器包含以下包：";
						libertine(id, "list-apps");
					}	//Libertine 操作 - 2
					else if (choice == 3) {
						char pack_name[100];
						cout << "请输入您需要查看的容器 ID：";
						cin.getline(id, 50);
						cout << "请输入您希望安装的桌面应用程序包名：";
						cin.getline(pack_name, 100);
						inst_pkg(id, pack_name);
						cout << "安装完毕。" << endl;
					}	//Libertine 操作 - 3
					else if (choice == 4) {
						char pack_name[100];
						cout << "请输入您需要查看的容器 ID：";
						cin.getline(id, 50);
						cout << "请输入您希望移除的桌面应用程序包名：";
						cin.getline(pack_name, 100);
						uninst_pkg(id, pack_name);
						cout << "移除完毕。" << endl;
					}	//Libertine 操作 - 4
					cout << endl;
				}	//Libertine 操作
			}
			cout << endl;
		}	//选项6
		else if (choice == 7) {
			cout << "请输入本地目标目录路径：";
			cin.getline(filepath1, 200);
			file_pull("/home/phablet/Pictures", filepath1);
			cout << endl;
		}
		else if (choice == 8) {
			cout << "输入管理员（超级用户权限）密码以完成操作\n";
			adb_shell("sudo mount -o remount,rw /");
		}
		else if (choice == 9) {
			system("adb reboot bootloader");
		}
		else if (choice == 10) {
			cout << "输入管理员（超级用户权限）密码以完成操作\n";
			system("adb shell sudo poweroff");
		}
		else if (choice == 11) {
			system("adb reboot");
		}
		else if (choice == 12) {
			system("adb reboot bootloader");
			system("fastboot format cache");
			system("fastboot format userdata");
			system("fastboot reboot");
		}
		else if (choice == 13) {
			system("fastboot reboot");
			cout << endl;
		}
		else if (choice == 14) {
			system("fastboot reboot recovery");
			cout << endl;
		}
		else if (choice == 15) {
			cout << "请输入 Recovery 镜像文件路径：";
			cin.getline(filepath1, 200);
			cout << "确保您的 Ubuntu Touch 设备已进入刷机模式（Fastboot）！\n";
			char str[500] = "fastboot flash recovery ";
			system(strcat(str, filepath1));
		}
		else if (choice == 16) {
			system("adb shell");
			cout << endl;
		}
		else if (choice == 17) {
			system("adb reconnect");
			system("adb devices");
		}
		else if (choice == 18) {
			system("adb get-serialno");
			cout << endl;
		}
	}	//功能列表循环
}
