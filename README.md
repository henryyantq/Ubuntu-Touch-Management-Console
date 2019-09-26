# Ubuntu-Touch-Management-Console
Connect your Ubuntu Touch device to your computer and manage it with UT Management Console.
将你的 Ubuntu Touch 设备连接至电脑并使用 Ubuntu Touch 设备管理终端进行操作。

- File transfer（一般文件传输）
- Export & import photo album(s)（导入/导出相册）
- Import videos & music (files or folder)（导入多媒体文件）
- External data backup（用户/外部数据备份）
- Terminal operations（终端访问操作）
- Anbox (Android-in-a-box) related operations（Anbox 安卓仿真运行环境相关操作）
- Libertine Container Management（Libertine 桌面应用程序容器管理）
- Bootloader (Fastboot mode) related operations（工程/刷机模式相关操作）
- More features will be added in the future. 更多的功能将逐渐推出。
- There may be some bugs at present, please understand. I'm still a rookie LOL! Thanks for your support and suggestions (if you have)! 目前可能存在一些程序问题，请谅解。我还是个开发小白 o(╥﹏╥)o 感谢你的支持！如果有任何建议或意见，请留言，谢谢！

Note: Whether Anbox related operations can be done depends on whether the Android emulator on your Ubuntu Touch device is working properly. If the operations fail, in most cases you might need to check if the Anbox on your UT device really works properly or not.（Anbox 安卓仿真运行环境相关操作的使用取决于您的设备是否支持 Anbox。程序中对 Anbox 支持的机型有所列举。你可以通过程序安装/重装 Anbox 运行环境。如果你已经正确安装了 Anbox，但程序读取 Anbox 时出现 Anbox 异常或无法正常进行 Anbox 相关操作，这可能是由于你设备中的 Anbox 运行环境暂时无法正常运行。你可以选择跟从程序的指示进行相关修复操作。）

This programme is only for Windows! I'll rewrite the terminal pipe operation to add support for Mac soon!
本程序目前仅支持在 Windows 系统下运行！我会在后续为更多的桌面平台提供支持！

About Wget: So far, Wget for UTMC must be placed under the folder where ADB setups are. If you place it under System32 directly, UTMC might not be able to detect and launch related options correctly in some cases.

About VC_Redist: So far, a few PCs have (32-bit's are more likely to) shown the issue 'missing api-ms-win-crt-runtimel1-1-0.dll' when initializing UTMC. The most efficient solution so far is installing VC_Redist as a widget (or something like that).
Attention: VC_Redist is not an essential widget for all PCs. Actually, the installation is only required after the issue above certainly shows up, since it might slows down the existed compiler(s) or runtime emvironment on your PC, which may cause unwanted trouble.

注意：不建议在大多数公共机房的 Windows 计算机上使用 UTMC，因为许多机器搭载的是经过定制的 Windows 系统，USB 端口适配性较低，可能出现 ADB 无法读取到您的设备的情况。对此我们并无解决方案，该问题也并非由 UTMC 及其插件的不完整性或不稳定性导致。建议您使用配备正版 Windows 操作系统（Windows 7 的较后期稳定版本、Windows 8.1 稳定版本与 Windows 10 稳定版本）的个人电脑操作 UTMC！

My emails:
yantq0927@gmail.com | henry0927@outlook.com

Find me on https://forums.ubports.com/ (UBports Forum): @Evergardener

通常，中文版更新进度较超前。请华人 UT 机友们尽量复制中文版的源码！
Sometimes, the update progress of Chinese version is more ahead of schedule. Sorry for the inconvenience!

感谢 Frank Pan，Ubuntu Touch 管理终端即将支持德语！
Dank Frank Pan wird das Ubuntu Touch Management Console bald Deutsch unterstützen!
