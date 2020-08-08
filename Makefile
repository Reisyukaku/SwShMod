tools := tools
schema := schema
src := src
build := build

.PHONY: all
all:
	@mkdir -p $(build)/bin/pokemon/table/
	@mkdir -p $(build)/bin/field/param/pokecenter/
	@mkdir -p $(build)/bin/pml/personal/
	$(tools)/flatc -o $(build)/bin/pokemon/table/ -b $(schema)/gfbpmcatalog.fbs $(src)/pokemon/table/poke_resource_table.json
	$(tools)/flatc -o $(build)/bin/pokemon/table/ -b $(schema)/gfbpmcatalog.fbs $(src)/pokemon/table/gpoke_resource_table.json
	$(tools)/flatc -o $(build)/bin/field/param/pokecenter/ -b $(schema)/recover.fbs $(src)/field/param/pokecenter/recovery.json
	$(tools)/PersonalParse -c $(src)/pml/personal/personal_total.json $(build)/bin/pml/personal/personal_total.bin
    
.PHONY: clean
clean:
	@rm -rf $(build)