# Bruno Mondelo Giaramita                                    
# mondelob14@gmail.com                                       
# isx48185462                                                
# Escola del Treball de Barcelona 2017-05-20

.SILENT:

# Convert to dzslides
PANDOC=pandoc --standalone --to dzslides
STYLE=#--css=

# The conversion files
TARGETS=msue.html

# The spanish version
ESFILE=msue-es.md

# The style files
STYLES=style.css

# RULES
all: $(TARGETS)

msue.html: msue.md
	echo "Creating slides for $@"
	$(PANDOC) $(INCREMENTAL) $(STYLE)$(STYLES) $< -o $@

# The utilities
build: clean all

show:
	echo "Showing slides..."
	firefox msue.html

build-es:
	echo "Creating slides in spanish"
	$(PANDOC) $(STYLE)$(STYLES) $(ESFILE) -o msue.html

clean:
	echo "Cleaning all targets"
	rm -f $(TARGETS)
