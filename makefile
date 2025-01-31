###############################################################
# 빌드 환경 및 규칙 설정
###############################################################
arm-linux-gnueabihf-
GCC64 = x86_64-pc-linux-gcc -g -c -m64 -ffreestanding
LD64 = x86_64-pc-linux-ld -melf_x86_64 -T ../elf_x86_64.x -nostdlib -e main -Ttext 0x200000
OBJCOPY64 = x86_64-pc-linux-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECTDIRECTORY = Temp
SOURCEDIRECTORY = Source


###############################################################
# 빌드 항목 및 빌드 방법 설정
###############################################################


all : prepare Kernel64.bin


prepare:
	mkdir -p $(OBJECTDIRECTORY)

dep:
	@echo === make dependency file ===
	make -C $(OBJECTDIRECTORY) -f ../makefile InternalDependency
	@echo === depency search complete ===

ExecuteInternalBuild: dep 
	make -C $(OBJECTDIRECTORY) -f ../makefile Kernel64.elf 


Kernel64.bin: ExecuteInternalBuild
	$(OBJCOPY64) $(OBJECTDIRECTORY)/Kernel64.elf $@

clean:
	rm -f *.bin
	rm -f $(OBJECTDIRECTORY)/*.*

###############################################################
# make에 의해 다시 호출되는 부분, Temp 디렉터리를 기준으로 수행됨
###############################################################
# 빌드할 어셈블리어 엔트리 포인트 소스 파일 정의, Temp 디렉터리 기준으로 설정 
ENTRYPOINTSOURCEFILE = ../$(SOURCEDIRECTORY)/EntryPoint.s
ENTRYPOINTOBJECTFILE = EntryPoint.o
# 빌드할 C 소스 파일 정의, Temp 디렉터리를 기준으로 설정
CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.c)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES =  $(notdir $(patsubst %.c,%.o,$(CSOURCEFILES)))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm,%.o,$(ASSEMBLYSOURCEFILES)))

# 어셈블리어 엔트리 포인트 빌드
$(ENTRYPOINTOBJECTFILE): $(ENTRYPOINTSOURCEFILE)
	$(NASM64) -o $@ $<

# .c 파일을 .o 파일로 바꾸는 규칙 정의
%.o: ../$(SOURCEDIRECTORY)/%.c
	$(GCC64) -c $<

# .asm 파일을 .o 파일로 바꾸는 규칙 정의
%.o: ../$(SOURCEDIRECTORY)/%.asm
	$(NASM64) -o $@ $<

InternalDependency:
	$(GCC64) -MM $(CSOURCEFILES) > dependency.dep 

Kernel64.elf: $(ENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD64) -o $@ $^


#ifeq (dependency.dep, $(wildcard dependency.dep))
-include dependency.dep 
#endif
