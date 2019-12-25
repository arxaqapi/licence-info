CC = gcc
CFLAGS = -Wall
EXEC = tsp_exec
INCDIR = includes/
LIBDIR = lib/

CFILES = main.c $(wildcard $(LIBDIR)*)
OFILES = $(subst lib/, , $(patsubst %.c, %.o, $(CFILES)))


YELLCOL = \033[33m
REDCOL = \033[91m
GREENCOL = \033[92m
LCYANCOL = \033[96m
CYANCOL = \033[36m
ENDCOL = \033[0m

all : $(EXEC)
	@echo "$(GREENCOL)Nettoyage du directoire principal$(ENDCOL)"
	@make cleanup \

$(EXEC) : libraries
	@echo "$(CYANCOL)Linking all objects files together$(ENDCOL)"
	@$(CC) $(CFLAGS) $(OFILES) -o $@ -I./$(INCDIR) \

libraries : $(CFILES)
	@echo "$(LCYANCOL)Compile all source files$(ENDCOL)"
	@$(CC) -c $^ -I$(INCDIR) \


cleanup:
	@rm *.o 

.PHONY: clean
clean:
	@rm -f $(EXEC) *.o