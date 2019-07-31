#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cstdio>
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

void backupf(char *file, char *target) {
	char pull[500] = "adb pull ";
	strcat(pull, file);
	strcat(pull, " ");
	strcat(pull, target);
	system(pull);
}

void get_img(char *code) {
	char cmd[200] = "wget http://cdimage.ubports.com/anbox-images/anbox-boot-";
	strcat(cmd, code);
	strcat(cmd, ".img");
	system(cmd);
}

void flash_img(char *code, char *part) {
	char cmd[200] = "fastboot flash ";
	strcat(cmd, part);
	strcat(cmd, " anbox-boot-");
	strcat(cmd, code);
	strcat(cmd, ".img");
	system(cmd);
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
	adb_shell(strcat(lib, id));
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

void mkdir(char *folder, char *backtype) {
	char dir[500] = "mkdir ";
	strcat(dir, folder);
	strcat(dir, "\\UTBackup-");
	strcat(dir, backtype);
	system(dir);
	char cur[500] = "";
	strcat(cur, folder);
	strcat(cur, "\\UTBackup-");
	strcat(cur, backtype);
	strcpy(folder, cur);
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
		cout << "2. 复制本地文件到设备指定目录\n3. 复制设备文件到本地指定目录\n4. 安装 Android 包到设备\n5. 卸载 Android 应用程序\n6. Libertine 桌面应用程序容器\n";
		cout << "7. 导入与导出设备相册\n8. 导入视频或音频文件\n9. 重载存储系统可读写\n10. 重启设备至刷机模式\n11. 强制关机\n12. 强制重新启动\n";
		cout << "13. 重新启动并还原出厂设置\n14. 从刷机模式重启至 Ubuntu Touch\n15. 从刷机模式重启至 Recovery\n16. 从刷机模式刷入非官方 Recovery\n17. 访问设备终端\n18. 手动访问 ADB\n19. 重新连接设备\n20. 获取设备序列号\n21. 备份您的 Ubuntu Touch 设备" << endl << "--> ";
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
			cout << "您的设备是否已经安装了 Anbox？\n1. 是的\n2. 未安装\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 1) {
instapk:
				while(1) {
					cout << endl << "本地安卓文件路径（输入“exit”并回车以退出）：";
					cin.getline(filepath1, 200);
					if (strcmp(filepath1, "exit") == 0) break;
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
				}
			}
			else if (choice == 2) {
				while (1) {
					cout << endl << "您是否需要现在安装 Anbox for Ubuntu？\n1. 什么是 Anbox？\n2. 好的，请为我安装。\n3. 退出安装 Anbox\n4. 前往安装 Android 应用程序\n--> ";
					cin >> choice;
					cin.get();
					if (choice == 1) {
						cout << endl << "Anbox 是 Linux 系统的 Android 模拟器。\n您在 Ubuntu Touch 上安装 Anbox，相当于在您的设备上安装了一个 Android 虚拟机。\n这使得您可以在 Ubuntu Touch 设备上安装并使用 Android 应用程序。\n如果您的设备购买自 Team Forth，您的设备将预置 Anbox，因此您可无需进行安装操作。\n\n请按回车键继续...";
						cin.get();
						cout << endl;
					}
					else if (choice == 2) {
						char codename[20];
						char partitionname[20];
						cout << endl << "如下设备支持部署 Anbox：\n1. Meizu Pro 5\n2. LG Nexus 5\n3. OnePlus One\n4. Fairphone 2\n5. BQ M10 HD\n6. BQ M10 FHD\n请选择您的设备：";
						cin >> choice;
						cin.get();
						if (choice == 1) {
							strcpy(codename, "turbo");
							strcpy(partitionname, "bootimg");
						}	// MEIZU
						else if (choice == 2) {
							strcpy(codename, "hammerhead");
							strcpy(partitionname, "boot");
						}	//NEXUS
						else if (choice == 3) {
							strcpy(codename, "bacon");
							strcpy(partitionname, "boot");
						}	//OPO
						else if (choice == 4) {
							strcpy(codename, "FP2");
							strcpy(partitionname, "boot");
						}	//FP2
						else if (choice == 6) {
							strcpy(codename, "frieza");
							strcpy(partitionname, "boot");
						}	//FHD
						else if (choice == 5) {
							strcpy(codename, "cooler");
							strcpy(partitionname, "boot");
						}	//HD
						cout << endl << "准备进入刷机模式..." << endl;
						adb_shell("sudo reboot -f bootloader");
						cout << "准备下载 Anbox 镜像文件..." << endl;
						get_img(codename);
						cout << "准备刷入 Anbox 镜像文件..." << endl;
						flash_img(codename, partitionname);
						cout << "准备重启..." << endl;
						system("fastboot reboot");
						cout << "重启至 Ubuntu Touch 后请按回车键继续！";
						cin.get();
						cout << "准备挂载系统分区为可读写..." << endl;
						adb_shell("sudo mount -o rw,remount /");
						cout << "准备升级 Aptitude 镜像源..." << endl;
						adb_shell("sudo apt update");
						cout << "准备下载 Anbox..." << endl;
						adb_shell("sudo apt install anbox-ubuntu-touch");
						cout << "准备安装..." << endl;
						adb_shell("anbox-tool install");
						cout << "准备安装 Android 调试桥..." << endl;
						adb_shell("sudo apt update");
						adb_shell("sudo apt install android-tools-adb");
						cout << endl;
						cout << "Anbox 及其附属插件已经完全安装！" << endl;
						cout << endl;
						goto instapk;
					}	//安装 Anbox
					else if (choice == 3) break;
					else if (choice == 4) {
						cout << endl;
						goto instapk;
					}
				}	// 安装 Anbox 与否
			}
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
			adb_shell("sudo mount -o rw,remount /");
			char lib_id[50];
			char lib_name[50];
			cout << "Libertine 容器管理\n\n";
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
			cout << "您希望\n1. 导入照片文件（夹）\n2. 导出...\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 2) {
				cout << "请输入本地目标目录路径：";
				cin.getline(filepath1, 200);
				file_pull("/home/phablet/Pictures", filepath1);
			}
			else if (choice == 1) {
				cout << "请输入本地相片文件（夹）路径：";
				cin.getline(filepath1, 200);
				file_push(filepath1, "/home/phablet/Pictures");
			}
			cout << endl;
		} 
		else if (choice == 8) {
			cout << "请输入本地视频或音频文件（夹）路径：";
			cin.getline(filepath1, 200);
			cout << "这是一个：\n1. 视频文件（夹）\n2. 音频文件（夹）\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 1)
				file_push(filepath1, "/home/phablet/Videos");
			else
				file_push(filepath1, "/home/phablet/Music");
			cout << endl;
		}
		else if (choice == 9) {
			cout << "输入管理员（超级用户权限）密码以完成操作\n";
			adb_shell("sudo mount -o rw,remount /");
		}
		else if (choice == 10) {
			system("adb reboot bootloader");
		}
		else if (choice == 11) {
			cout << "输入管理员（超级用户权限）密码以完成操作\n";
			system("adb shell sudo poweroff");
		}
		else if (choice == 12) {
			system("adb reboot");
		}
		else if (choice == 13) {
			system("adb reboot bootloader");
			system("fastboot format cache");
			system("fastboot format userdata");
			system("fastboot reboot");
		}
		else if (choice == 14) {
			system("fastboot reboot");
			cout << endl;
		}
		else if (choice == 15) {
			system("fastboot reboot recovery");
			cout << endl;
		}
		else if (choice == 16) {
			cout << "请输入 Recovery 镜像文件路径：";
			cin.getline(filepath1, 200);
			cout << "确保您的 Ubuntu Touch 设备已进入刷机模式（Fastboot）！\n";
			char str[500] = "fastboot flash recovery ";
			system(strcat(str, filepath1));
			cout << endl;
		}
		else if (choice == 17) {
			system("adb shell");
			cout << endl;
		}
		else if (choice == 18) {
			system("adb");
			int i = 0;
			while(1) {
				char line[500];
				if (i == 0)
					cout << endl << "输入 ADB 指令：";
				else cout << "输入 ADB 指令（输入 \"exit\"退出 ADB）：";
				cin.getline(line, 500);
				if (!strcmp(line, "exit")) break;
				else if (!strcmp(line, "adb")) cout << endl;
				system(line);
				i++;
			}
			cout << endl;
		}
		else if (choice == 19) {
			system("adb reconnect");
			system("adb devices");
		}
		else if (choice == 20) {
			system("adb get-serialno");
			cout << endl;
		}
		else if (choice == 21) {
			cout << "请输入需要备份到的本地文件目录（文件夹）路径：";
			cin.getline(filepath1, 200);
			cout << "您的设备是否已部署了 Anbox？\n1. 是的\n2. 没有\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 1) {
				cout << endl << "我们可以为您备份 Anbox 数据，但如果您需要抹去所有数据，您的 Ubuntu Touch 将需要被重新安装！\n";
			}
			cout << endl << "请选择备份数据\n1. 全部资料\n2. 所有多媒体数据（音/视频、图片）\n3. 下载内容\n4. 文档\n--> ";
			cin >> choice;
			cin.get();
			cout << endl;
			if (choice == 1) {
				mkdir(filepath1, "all");
				backupf("/home/phablet/anbox-data", filepath1);
				backupf("/home/phablet/Desktop", filepath1);
				backupf("/home/phablet/Documents", filepath1);
				backupf("/home/phablet/Downloads", filepath1);
				backupf("/home/phablet/Music", filepath1);
				backupf("/home/phablet/Pictures", filepath1);
				backupf("/home/phablet/Public", filepath1);
				backupf("/home/phablet/Templates", filepath1);
				backupf("/home/phablet/Videos", filepath1);
			}	//备份全部资料
			else if (choice == 2) {
				mkdir(filepath1, "media");
				backupf("/home/phablet/Music", filepath1);
				backupf("/home/phablet/Pictures", filepath1);
				backupf("/home/phablet/Videos", filepath1);
			}	//所有多媒体数据
			else if (choice == 3) {
				mkdir(filepath1, "downs");
				backupf("/home/phablet/Downloads", filepath1);
			}	//备份下载内容
			else if (choice == 4) {
				mkdir(filepath1, "docs");
				backupf("/home/phablet/Documents", filepath1);
			}	//备份文档
			cout << endl << "备份已完成！" << endl << endl;
		}
	}	//功能列表循环
}
