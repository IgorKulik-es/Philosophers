NAME = philo
BONUSNAME = philo_bonus

SRC = philo_main.c threader.c cleaner.c initializer.c basics.c
BONUSSRC =

SRCSDIR = src
OBJDIR = obj

SRCS = $(addprefix $(SRCSDIR)/, $(SRC))
BONUSSRCS = $(addprefix $(OBJDIR)/, $(BONUSSRC))

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
BONUSOBJS = $(addprefix $(OBJDIR)/,  $(notdir $(BONUSSRCS:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -lpthread

RM = rm -f

all: $(NAME)
bonus: $(BONUSNAME)

$(NAME): $(LIBRARY) $(OBJS)
	cc $(OBJS) $(LIBRARY) -o $(NAME) $(MFLAGS)

$(BONUSNAME): $(BONUSOBJS) $(LIBRARY)
	cc $(BONUSOBJS) $(LIBRARY) $(MFLAGS) -o $(BONUSNAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(RM) $(NAME) $(BONUSNAME)

re: fclean all
