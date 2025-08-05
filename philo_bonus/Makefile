NAME = philo_bonus

SRC = philo_main_bonus.c threader_bonus.c cleaner_bonus.c initializer_bonus.c\
basics.c monitor_bonus.c

SRCSDIR = src
OBJDIR = obj

SRCS = $(addprefix $(SRCSDIR)/, $(SRC))

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -lpthread

RM = rm -f

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJDIR) $(OBJS)
	cc $(OBJS) $(LIBRARY) -o $(NAME) $(MFLAGS)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(RM) $(NAME) $(BONUSNAME)

re: fclean all

.PHONY: all clean fclean re
