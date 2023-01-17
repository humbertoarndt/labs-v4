/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:00:04 by harndt            #+#    #+#             */
/*   Updated: 2023/01/09 20:24:24 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// =============================================================================
// EOF
// =============================================================================

# define eof	"\033[0m"      // Text Reset

// =============================================================================
// REGULAR
// =============================================================================

# define black	"\033[0;30m"        // Black
# define red	"\033[0;31m"          // Red
# define green	"\033[0;32m"        // Green
# define yellow	"\033[0;33m"       // Yellow
# define blue	"\033[0;34m"         // Blue
# define purple	"\033[0;35m"       // Purple
# define cyan	"\033[0;36m"         // Cyan
# define white	"\033[0;37m"        // White

// =============================================================================
// BOLD
// =============================================================================

# define bblack		"\033[1;30m"       // Black
# define bred		"\033[1;31m"         // Red
# define bgreen		"\033[1;32m"       // Green
# define byellow	"\033[1;33m"      // Yellow
# define byblue		"\033[1;34m"        // Blue
# define bpurple	"\033[1;35m"      // Purple
# define bcyan		"\033[1;36m"        // Cyan
# define bwhite		"\033[1;37m"       // White

// =============================================================================
// UNDERLINE
// =============================================================================

# define ublack		"\033[4;30m"       // Black
# define ured		"\033[4;31m"         // Red
# define ugreen		"\033[4;32m"       // Green
# define uyellow	"\033[4;33m"      // Yellow
# define ublue		"\033[4;34m"        // Blue
# define upruple	"\033[4;35m"      // Purple
# define ucyan		"\033[4;36m"        // Cyan
# define uwhite		"\033[4;37m"       // White

// =============================================================================
// BACKGROUND
// =============================================================================

# define bgblack	"\033[40m"       // Black
# define bgred		"\033[41m"         // Red
# define bggreen	"\033[42m"       // Green
# define bgyellow	"\033[43m"      // Yellow
# define bgblue		"\033[44m"        // Blue
# define bgpurple	"\033[45m"      // Purple
# define bgcyan		"\033[46m"        // Cyan
# define bgwhite	"\033[47m"       // White

// =============================================================================
// HIGH INTENSITY
// =============================================================================

# define iblack		"\033[0;90m"       // Black
# define ired		"\033[0;91m"         // Red
# define igreen		"\033[0;92m"       // Green
# define iyellow	"\033[0;93m"      // Yellow
# define iblue		"\033[0;94m"        // Blue
# define ipurple	"\033[0;95m"      // Purple
# define icyan		"\033[0;96m"        // Cyan
# define iwhite		"\033[0;97m"       // White

// =============================================================================
// BOLD HIGH INTENSITY
// =============================================================================

# define biblack	"\033[1;90m"      // Black
# define bired		"\033[1;91m"        // Red
# define bigreen	"\033[1;92m"      // Green
# define biyellow	"\033[1;93m"     // Yellow
# define biblue		"\033[1;94m"       // Blue
# define bipurple	"\033[1;95m"     // Purple
# define bicyan		"\033[1;96m"       // Cyan
# define biwhite	"\033[1;97m"      // White

// =============================================================================
// HIGH INTENSITY BACKGROUNDS
// =============================================================================
# define oniblack	"\033[0;100m"   // Black
# define onired		"\033[0;101m"     // Red
# define onidegreen	"\033[0;102m"   // Green
# define oniyellow	"\033[0;103m"  // Yellow
# define oniblue	"\033[0;104m"    // Blue
# define onipurple	"\033[0;105m"  // Purple
# define oniecyan	"\033[0;106m"    // Cyan
# define oniwhite	"\033[0;107m"   // White

#endif