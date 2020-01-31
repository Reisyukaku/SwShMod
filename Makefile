tools := tools
schema := schema
src := src
build := build

.PHONY: all
all:
	@mkdir -p $(build)/bin/pokemon/table/
	@mkdir -p $(build)/bin/field/param/pokecenter/
	$(tools)/flatc -o $(build)/bin/pokemon/table/ -b $(schema)/gfbpmcatalog.fbs $(src)/misc/poke_resource_table.json
	$(tools)/flatc -o $(build)/bin/pokemon/table/ -b $(schema)/gfbpmcatalog.fbs $(src)/misc/gpoke_resource_table.json
	$(tools)/flatc -o $(build)/bin/field/param/pokecenter/ -b $(schema)/recover.fbs $(src)/misc/recovery.json
    
.PHONY: clean
clean:
	@rm -rf $(build)