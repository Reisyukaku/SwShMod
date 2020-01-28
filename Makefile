tools := tools
schema := schema
src := src
build := build

.PHONY: all
all:
	@mkdir -p $(build)/bin/pokemon/table/
	@mkdir -p $(build)/bin/field/param/pokecenter/
	$(tools)/flatc -b $(schema)/gfbpmcatalog.fbs $(src)/poke_resource_table.json
	$(tools)/flatc -b $(schema)/gfbpmcatalog.fbs $(src)/gpoke_resource_table.json
	$(tools)/flatc -b $(schema)/recover.fbs $(src)/recovery.json
	@mv poke_resource_table.bin $(build)/bin/pokemon/table/poke_resource_table.gfbpmcatalog
	@mv gpoke_resource_table.bin $(build)/bin/pokemon/table/gpoke_resource_table.gfbpmcatalog
	@mv recovery.bin $(build)/bin/field/param/pokecenter/recovery.bin
    
.PHONY: clean
clean:
	@rm -rf $(build)