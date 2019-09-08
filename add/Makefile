FILENAME = index

wasm: $(FILENAME).c 
	clang \
				-Wall \
				--target=wasm32 \
				-Os \
				-nostdlib \
				-Wl,--no-entry \
				-Wl,--export-dynamic \
				-Wl,--allow-undefined \
				-o $(FILENAME).wasm \
				$(FILENAME).c
				# -Wl,--max-memory  
				# -Wl,--import-memory 


ir: $(FILENAME).cpp
	clang \
			--target=wasm32 \
			-emit-llvm \
			-c \
			-S \
			$(FILENAME).cpp

obj: $(FILENAME).ll
	llc -march=wasm32 \
			-filetype=obj \
			(FILENAME).ll

ld: $(FILENAME).o
	wasm-ld --no-entry \
			--export-dynamic \
			--allow-undefined \
			-o $(FILENAME).wasm \
			$(FILENAME).o

wat:$(FILENAME).wasm
	wasm2wat $(FILENAME).wasm > $(FILENAME).wat

clean:
	rm -rf *.wat *.o *.wasm *.ll