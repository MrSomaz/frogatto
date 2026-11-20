// Stubs for POSIX APIs unavailable in the browser.
extern "C" int shmdt(const void*) { return -1; }
