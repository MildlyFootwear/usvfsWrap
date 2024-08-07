// lpApplicationName should be the full path to the executable. lpCommandLine will be the arguments passed to it as if they were right after it in a shortcut. Executing thread will halt until the launched application exits. It'd be wise to create a dedicated thread to launch from.

[DllImport("usvfsWrap.dll")] public static extern bool usvfsWrapCreateProcessHooked(string lpApplicationName, string lpCommandLine);

// Functions exactly like usvfsVirtualLinkDirectoryStatic, except plain string arguments can be passed to it.

[DllImport("usvfsWrap.dll")] public static extern void usvfsWrapVirtualLinkDirectoryStatic(string source, string destination, uint flags);

// Functions exactly like usvfsVirtualLinkFile, except plain string arguments can be passed to it.

[DllImport("usvfsWrap.dll")] public static extern void usvfsWrapVirtualLinkFile(string source, string destination, uint flags);

// Produces a pointer to a character array containing the structure of the VFS. Pass as an argument to Marshal.PtrToStringAnsi (i.e. "string s = Marshal.PtrToStringAnsi(usvfsWrapCreateVFSDump());") to get as a string.

[DllImport("usvfsWrap.dll")] public static extern unsafe IntPtr usvfsWrapCreateVFSDump();

// Returns an int representing the number of processes hooked into the VFS.

[DllImport("usvfsWrap.dll")] public static extern int usvfsWrapGetHookedCount();

// Functions exactly like usvfsAddSkipFileSuffix, except plain string arguments can be passed to it.

[DllImport("usvfsWrap.dll")] public static extern void usvfsWrapAddSkipFileSuffix(string source, string destination);

// Functions exactly like usvfsAddSkipDirectory, except plain string arguments can be passed to it.

[DllImport("usvfsWrap.dll")] public static extern void usvfsWrapAddSkipDirectory(string source, string destination);

// Can be used to set debug mode for usvfsWrap functions, where it will print the name of functions as they execute along with the arguments passed to them.

[DllImport("usvfsWrap.dll")] public static extern void usvfsWrapSetDebug(bool b);