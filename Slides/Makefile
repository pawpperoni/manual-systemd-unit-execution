# Bruno Mondelo Giaramita                                    
# mondelob14@gmail.com                                       
# isx48185462                                                
# Escola del Treball de Barcelona 2017-05-20

.SILENT:

# Convert to dzslides
PANDOC=pandoc --standalone --to dzslides
INCREMENTAL=#--incremental

# The conversion files
TARGETS=msue.html

# RULES
all: $(TARGETS)

msue.html: msue.md
	echo "Creating slides for $@"
	$(PANDOC) $(INCREMENTAL) $< -o $@

# The utilities
build: clean all

clean:
	rm -f $(TARGETS)
