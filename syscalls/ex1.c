// write (g)libc wrapper call directly
// examine this program with debugger by disassembling 

void main()
{
	write(1, "hello", 5); // stdout , string, "strlen(stdout)"
	return;
}
