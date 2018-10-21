/* ******************************************************************************* */
/* ******************************** Copyright (C) ******************************** */
/* ******************************************************************************* */
/*                                                                                 */
/* This file is part of USBTest Suite.                                             */
/*                                                                                 */
/* USBTest Suite is free software; you can redistribute it and/or                  */
/* modify it under the terms of the GNU General Public License                     */
/* as published by the Free Software Foundation; either version 2                  */
/* of the License, or (at your option) any later version.                          */
/*                                                                                 */
/* USBTest Suite is distributed in the hope that it will be useful,                */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of                  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   */
/* GNU General Public License for more details.                                    */
/*                                                                                 */
/* You should have received a copy of the GNU General Public License               */
/* along with USBTest Suite; if not, write to the Free Software                    */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */
/*                                                                                 */
/* Copyright (C) 2018  Amine Hmidi (amine.hmidi0.1@gmail.com)                      */
/*                                                                                 */
/* ******************************************************************************* */

/* C++ Includes */
#include <iostream>
#include <string>
#include <sstream>

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"


/* **************************************************************************************************** */
/* ********************************** Display CopyRights and Warraty ********************************** */
/* **************************************************************************************************** */


void USBTestCli::DisplayCopyRights()
{
    std::stringstream stream;

    stream << "	            GNU GENERAL PUBLIC LICENSE                                        \n";
    stream << "	               Version 2, June 1991                                           \n";
    stream << "                                                                               \n";
    stream << "Copyright (C) 1989, 1991 Free Software Foundation, Inc.,                       \n";
    stream << "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA                     \n";
    stream << "Everyone is permitted to copy and distribute verbatim copies                   \n";
    stream << "of this license document, but changing it is not allowed.                      \n";
    stream << "                                                                               \n";
    stream << "                      Preamble                                                 \n";
    stream << "                                                                               \n";
    stream << "  The licenses for most software are designed to take away your                \n";
    stream << "freedom to share and change it.  By contrast, the GNU General Public           \n";
    stream << "License is intended to guarantee your freedom to share and change free         \n";
    stream << "software--to make sure the software is free for all its users.  This           \n";
    stream << "General Public License applies to most of the Free Software                    \n";
    stream << "Foundation's software and to any other program whose authors commit to         \n";
    stream << "using it.  (Some other Free Software Foundation software is covered by         \n";
    stream << "the GNU Lesser General Public License instead.)  You can apply it to           \n";
    stream << "your programs, too.                                                            \n";
    stream << "                                                                               \n";
    stream << "  When we speak of free software, we are referring to freedom, not             \n";
    stream << "price.  Our General Public Licenses are designed to make sure that you         \n";
    stream << "have the freedom to distribute copies of free software (and charge for         \n";
    stream << "this service if you wish), that you receive source code or can get it          \n";
    stream << "if you want it, that you can change the software or use pieces of it           \n";
    stream << "in new free programs; and that you know you can do these things.               \n";
    stream << "                                                                               \n";
    stream << "  To protect your rights, we need to make restrictions that forbid             \n";
    stream << "anyone to deny you these rights or to ask you to surrender the rights.         \n";
    stream << "These restrictions translate to certain responsibilities for you if you        \n";
    stream << "distribute copies of the software, or if you modify it.                        \n";
    stream << "                                                                               \n";
    stream << "  For example, if you distribute copies of such a program, whether             \n";
    stream << "gratis or for a fee, you must give the recipients all the rights that          \n";
    stream << "you have.  You must make sure that they, too, receive or can get the           \n";
    stream << "source code.  And you must show them these terms so they know their            \n";
    stream << "rights.                                                                        \n";
    stream << "                                                                               \n";
    stream << "  We protect your rights with two steps: (1) copyright the software, and       \n";
    stream << "(2) offer you this license which gives you legal permission to copy,           \n";
    stream << "distribute and/or modify the software.                                         \n";
    stream << "                                                                               \n";
    stream << "  Also, for each author's protection and ours, we want to make certain         \n";
    stream << "that everyone understands that there is no warranty for this free              \n";
    stream << "software.  If the software is modified by someone else and passed on, we       \n";
    stream << "want its recipients to know that what they have is not the original, so        \n";
    stream << "that any problems introduced by others will not reflect on the original        \n";
    stream << "authors' reputations.                                                          \n";
    stream << "                                                                               \n";
    stream << "  Finally, any free program is threatened constantly by software               \n";
    stream << "patents.  We wish to avoid the danger that redistributors of a free            \n";
    stream << "program will individually obtain patent licenses, in effect making the         \n";
    stream << "program proprietary.  To prevent this, we have made it clear that any          \n";
    stream << "patent must be licensed for everyone's free use or not licensed at all.        \n";
    stream << "                                                                               \n";
    stream << "  The precise terms and conditions for copying, distribution and               \n";
    stream << "modification follow.                                                           \n";
    stream << "                                                                               \n";
    stream << "              GNU GENERAL PUBLIC LICENSE                                       \n";
    stream << "     TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION           \n";
    stream << "                                                                               \n";
    stream << "  0. This License applies to any program or other work which contains          \n";
    stream << "a notice placed by the copyright holder saying it may be distributed           \n";
    stream << "under the terms of this General Public License.  The \"Program\", below,       \n";
    stream << "refers to any such program or work, and a \"work based on the Program\"        \n";
    stream << "means either the Program or any derivative work under copyright law:           \n";
    stream << "that is to say, a work containing the Program or a portion of it,              \n";
    stream << "either verbatim or with modifications and/or translated into another           \n";
    stream << "language.  (Hereinafter, translation is included without limitation in         \n";
    stream << "the term \"modification\".)  Each licensee is addressed as \"you\".            \n";
    stream << "                                                                               \n";
    stream << "Activities other than copying, distribution and modification are not           \n";
    stream << "covered by this License; they are outside its scope.  The act of               \n";
    stream << "running the Program is not restricted, and the output from the Program         \n";
    stream << "is covered only if its contents constitute a work based on the                 \n";
    stream << "Program (independent of having been made by running the Program).              \n";
    stream << "Whether that is true depends on what the Program does.                         \n";
    stream << "                                                                               \n";
    stream << "  1. You may copy and distribute verbatim copies of the Program's              \n";
    stream << "source code as you receive it, in any medium, provided that you                \n";
    stream << "conspicuously and appropriately publish on each copy an appropriate            \n";
    stream << "copyright notice and disclaimer of warranty; keep intact all the               \n";
    stream << "notices that refer to this License and to the absence of any warranty;         \n";
    stream << "and give any other recipients of the Program a copy of this License            \n";
    stream << "along with the Program.                                                        \n";
    stream << "                                                                               \n";
    stream << "You may charge a fee for the physical act of transferring a copy, and          \n";
    stream << "you may at your option offer warranty protection in exchange for a fee.        \n";
    stream << "                                                                               \n";
    stream << "  2. You may modify your copy or copies of the Program or any portion          \n";
    stream << "of it, thus forming a work based on the Program, and copy and                  \n";
    stream << "distribute such modifications or work under the terms of Section 1             \n";
    stream << "above, provided that you also meet all of these conditions:                    \n";
    stream << "                                                                               \n";
    stream << "      a) You must cause the modified files to carry prominent notices          \n";
    stream << "      stating that you changed the files and the date of any change.           \n";
    stream << "                                                                               \n";
    stream << "      b) You must cause any work that you distribute or publish, that in       \n";
    stream << "      whole or in part contains or is derived from the Program or any          \n";
    stream << "      part thereof, to be licensed as a whole at no charge to all third        \n";
    stream << "      parties under the terms of this License.                                 \n";
    stream << "                                                                               \n";
    stream << "      c) If the modified program normally reads commands interactively         \n";
    stream << "      when run, you must cause it, when started running for such               \n";
    stream << "      interactive use in the most ordinary way, to print or display an         \n";
    stream << "      announcement including an appropriate copyright notice and a             \n";
    stream << "      notice that there is no warranty (or else, saying that you provide       \n";
    stream << "      a warranty) and that users may redistribute the program under            \n";
    stream << "      these conditions, and telling the user how to view a copy of this        \n";
    stream << "      License.  (Exception: if the Program itself is interactive but           \n";
    stream << "      does not normally print such an announcement, your work based on         \n";
    stream << "      the Program is not required to print an announcement.)                   \n";
    stream << "                                                                               \n";
    stream << "These requirements apply to the modified work as a whole.  If                  \n";
    stream << "identifiable sections of that work are not derived from the Program,           \n";
    stream << "and can be reasonably considered independent and separate works in             \n";
    stream << "themselves, then this License, and its terms, do not apply to those            \n";
    stream << "sections when you distribute them as separate works.  But when you             \n";
    stream << "distribute the same sections as part of a whole which is a work based          \n";
    stream << "on the Program, the distribution of the whole must be on the terms of          \n";
    stream << "this License, whose permissions for other licensees extend to the              \n";
    stream << "entire whole, and thus to each and every part regardless of who wrote it.      \n";
    stream << "                                                                               \n";
    stream << "Thus, it is not the intent of this section to claim rights or contest          \n";
    stream << "your rights to work written entirely by you; rather, the intent is to          \n";
    stream << "exercise the right to control the distribution of derivative or                \n";
    stream << "collective works based on the Program.                                         \n";
    stream << "                                                                               \n";
    stream << "In addition, mere aggregation of another work not based on the Program         \n";
    stream << "with the Program (or with a work based on the Program) on a volume of          \n";
    stream << "a storage or distribution medium does not bring the other work under           \n";
    stream << "the scope of this License.                                                     \n";
    stream << "                                                                               \n";
    stream << "  3. You may copy and distribute the Program (or a work based on it,           \n";
    stream << "under Section 2) in object code or executable form under the terms of          \n";
    stream << "Sections 1 and 2 above provided that you also do one of the following:         \n";
    stream << "                                                                               \n";
    stream << "      a) Accompany it with the complete corresponding machine-readable         \n";
    stream << "      source code, which must be distributed under the terms of Sections       \n";
    stream << "      1 and 2 above on a medium customarily used for software interchange; or, \n";
    stream << "                                                                               \n";
    stream << "      b) Accompany it with a written offer, valid for at least three           \n";
    stream << "      years, to give any third party, for a charge no more than your           \n";
    stream << "      cost of physically performing source distribution, a complete            \n";
    stream << "      machine-readable copy of the corresponding source code, to be            \n";
    stream << "      distributed under the terms of Sections 1 and 2 above on a medium        \n";
    stream << "      customarily used for software interchange; or,                           \n";
    stream << "                                                                               \n";
    stream << "      c) Accompany it with the information you received as to the offer        \n";
    stream << "      to distribute corresponding source code.  (This alternative is           \n";
    stream << "      allowed only for noncommercial distribution and only if you              \n";
    stream << "      received the program in object code or executable form with such         \n";
    stream << "      an offer, in accord with Subsection b above.)                            \n";
    stream << "                                                                               \n";
    stream << "The source code for a work means the preferred form of the work for            \n";
    stream << "making modifications to it.  For an executable work, complete source           \n";
    stream << "code means all the source code for all modules it contains, plus any           \n";
    stream << "associated interface definition files, plus the scripts used to                \n";
    stream << "control compilation and installation of the executable.  However, as a         \n";
    stream << "special exception, the source code distributed need not include                \n";
    stream << "anything that is normally distributed (in either source or binary              \n";
    stream << "form) with the major components (compiler, kernel, and so on) of the           \n";
    stream << "operating system on which the executable runs, unless that component           \n";
    stream << "itself accompanies the executable.                                             \n";
    stream << "                                                                               \n";
    stream << "If distribution of executable or object code is made by offering               \n";
    stream << "access to copy from a designated place, then offering equivalent               \n";
    stream << "access to copy the source code from the same place counts as                   \n";
    stream << "distribution of the source code, even though third parties are not             \n";
    stream << "compelled to copy the source along with the object code.                       \n";
    stream << "                                                                               \n";
    stream << "  4. You may not copy, modify, sublicense, or distribute the Program           \n";
    stream << "except as expressly provided under this License.  Any attempt                  \n";
    stream << "otherwise to copy, modify, sublicense or distribute the Program is             \n";
    stream << "void, and will automatically terminate your rights under this License.         \n";
    stream << "However, parties who have received copies, or rights, from you under           \n";
    stream << "this License will not have their licenses terminated so long as such           \n";
    stream << "parties remain in full compliance.                                             \n";
    stream << "                                                                               \n";
    stream << "  5. You are not required to accept this License, since you have not           \n";
    stream << "signed it.  However, nothing else grants you permission to modify or           \n";
    stream << "distribute the Program or its derivative works.  These actions are             \n";
    stream << "prohibited by law if you do not accept this License.  Therefore, by            \n";
    stream << "modifying or distributing the Program (or any work based on the                \n";
    stream << "Program), you indicate your acceptance of this License to do so, and           \n";
    stream << "all its terms and conditions for copying, distributing or modifying            \n";
    stream << "the Program or works based on it.                                              \n";
    stream << "                                                                               \n";
    stream << "  6. Each time you redistribute the Program (or any work based on the          \n";
    stream << "Program), the recipient automatically receives a license from the              \n";
    stream << "original licensor to copy, distribute or modify the Program subject to         \n";
    stream << "these terms and conditions.  You may not impose any further                    \n";
    stream << "restrictions on the recipients' exercise of the rights granted herein.         \n";
    stream << "You are not responsible for enforcing compliance by third parties to           \n";
    stream << "this License.                                                                  \n";
    stream << "                                                                               \n";
    stream << "  7. If, as a consequence of a court judgment or allegation of patent          \n";
    stream << "infringement or for any other reason (not limited to patent issues),           \n";
    stream << "conditions are imposed on you (whether by court order, agreement or            \n";
    stream << "otherwise) that contradict the conditions of this License, they do not         \n";
    stream << "excuse you from the conditions of this License.  If you cannot                 \n";
    stream << "distribute so as to satisfy simultaneously your obligations under this         \n";
    stream << "License and any other pertinent obligations, then as a consequence you         \n";
    stream << "may not distribute the Program at all.  For example, if a patent               \n";
    stream << "license would not permit royalty-free redistribution of the Program by         \n";
    stream << "all those who receive copies directly or indirectly through you, then          \n";
    stream << "the only way you could satisfy both it and this License would be to            \n";
    stream << "refrain entirely from distribution of the Program.                             \n";
    stream << "                                                                               \n";
    stream << "If any portion of this section is held invalid or unenforceable under          \n";
    stream << "any particular circumstance, the balance of the section is intended to         \n";
    stream << "apply and the section as a whole is intended to apply in other                 \n";
    stream << "circumstances.                                                                 \n";
    stream << "                                                                               \n";
    stream << "It is not the purpose of this section to induce you to infringe any            \n";
    stream << "patents or other property right claims or to contest validity of any           \n";
    stream << "such claims; this section has the sole purpose of protecting the               \n";
    stream << "integrity of the free software distribution system, which is                   \n";
    stream << "implemented by public license practices.  Many people have made                \n";
    stream << "generous contributions to the wide range of software distributed               \n";
    stream << "through that system in reliance on consistent application of that              \n";
    stream << "system; it is up to the author/donor to decide if he or she is willing         \n";
    stream << "to distribute software through any other system and a licensee cannot          \n";
    stream << "impose that choice.                                                            \n";
    stream << "                                                                               \n";
    stream << "This section is intended to make thoroughly clear what is believed to          \n";
    stream << "be a consequence of the rest of this License.                                  \n";
    stream << "                                                                               \n";
    stream << "  8. If the distribution and/or use of the Program is restricted in            \n";
    stream << "certain countries either by patents or by copyrighted interfaces, the          \n";
    stream << "original copyright holder who places the Program under this License            \n";
    stream << "may add an explicit geographical distribution limitation excluding             \n";
    stream << "those countries, so that distribution is permitted only in or among            \n";
    stream << "countries not thus excluded.  In such case, this License incorporates          \n";
    stream << "the limitation as if written in the body of this License.                      \n";
    stream << "                                                                               \n";
    stream << "  9. The Free Software Foundation may publish revised and/or new versions      \n";
    stream << "of the General Public License from time to time.  Such new versions will       \n";
    stream << "be similar in spirit to the present version, but may differ in detail to       \n";
    stream << "address new problems or concerns.                                              \n";
    stream << "                                                                               \n";
    stream << "Each version is given a distinguishing version number.  If the Program         \n";
    stream << "specifies a version number of this License which applies to it and \"any       \n";
    stream << "later version\", you have the option of following the terms and conditions     \n";
    stream << "either of that version or of any later version published by the Free           \n";
    stream << "Software Foundation.  If the Program does not specify a version number of      \n";
    stream << "this License, you may choose any version ever published by the Free Software   \n";
    stream << "Foundation.                                                                    \n";
    stream << "                                                                               \n";
    stream << "  10. If you wish to incorporate parts of the Program into other free          \n";
    stream << "programs whose distribution conditions are different, write to the author      \n";
    stream << "to ask for permission.  For software which is copyrighted by the Free          \n";
    stream << "Software Foundation, write to the Free Software Foundation; we sometimes       \n";
    stream << "make exceptions for this.  Our decision will be guided by the two goals        \n";
    stream << "of preserving the free status of all derivatives of our free software and      \n";
    stream << "of promoting the sharing and reuse of software generally.                      \n";
    stream << "                                                                               \n";
    stream << "                NO WARRANTY                                                    \n";
    stream << "                                                                               \n";
    stream << "  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY     \n";
    stream << "FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN       \n";
    stream << "OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES         \n";
    stream << "PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED   \n";
    stream << "OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           \n";
    stream << "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS      \n";
    stream << "TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE         \n";
    stream << "PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,       \n";
    stream << "REPAIR OR CORRECTION.                                                          \n";
    stream << "                                                                               \n";
    stream << "  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING    \n";
    stream << "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR            \n";
    stream << "REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,     \n";
    stream << "INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING    \n";
    stream << "OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED      \n";
    stream << "TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY       \n";
    stream << "YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER     \n";
    stream << "PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE          \n";
    stream << "POSSIBILITY OF SUCH DAMAGES.                                                   \n";
    stream << "                                                                               \n";
    stream << "             END OF TERMS AND CONDITIONS                                       \n";
    stream << "                                                                               \n";
    stream << "        How to Apply These Terms to Your New Programs                          \n";
    stream << "                                                                               \n";
    stream << "  If you develop a new program, and you want it to be of the greatest          \n";
    stream << "possible use to the public, the best way to achieve this is to make it         \n";
    stream << "free software which everyone can redistribute and change under these terms.    \n";
    stream << "                                                                               \n";
    stream << "  To do so, attach the following notices to the program.  It is safest         \n";
    stream << "to attach them to the start of each source file to most effectively            \n";
    stream << "convey the exclusion of warranty; and each file should have at least           \n";
    stream << "the \"copyright\" line and a pointer to where the full notice is found.        \n";
    stream << "                                                                               \n";
    stream << "    <one line to give the program's name and a brief idea of what it does.>    \n";
    stream << "    Copyright (C) <year>  <name of author>                                     \n";
    stream << "                                                                               \n";
    stream << "    This program is free software; you can redistribute it and/or modify       \n";
    stream << "    it under the terms of the GNU General Public License as published by       \n";
    stream << "    the Free Software Foundation; either version 2 of the License, or          \n";
    stream << "    (at your option) any later version.                                        \n";
    stream << "                                                                               \n";
    stream << "    This program is distributed in the hope that it will be useful,            \n";
    stream << "    but WITHOUT ANY WARRANTY; without even the implied warranty of             \n";
    stream << "    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              \n";
    stream << "    GNU General Public License for more details.                               \n";
    stream << "                                                                               \n";
    stream << "    You should have received a copy of the GNU General Public License along    \n";
    stream << "    with this program; if not, write to the Free Software Foundation, Inc.,    \n";
    stream << "    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                \n";
    stream << "                                                                               \n";
    stream << "Also add information on how to contact you by electronic and paper mail.       \n";
    stream << "                                                                               \n";
    stream << "If the program is interactive, make it output a short notice like this         \n";
    stream << "when it starts in an interactive mode:                                         \n";
    stream << "                                                                               \n";
    stream << "    Gnomovision version 69, Copyright (C) year name of author                  \n";
    stream << "    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.  \n";
    stream << "    This is free software, and you are welcome to redistribute it              \n";
    stream << "    under certain conditions; type `show c' for details.                       \n";
    stream << "                                                                               \n";
    stream << "The hypothetical commands `show w' and `show c' should show the appropriate    \n";
    stream << "parts of the General Public License.  Of course, the commands you use may      \n";
    stream << "be called something other than `show w' and `show c'; they could even be       \n";
    stream << "mouse-clicks or menu items--whatever suits your program.                       \n";
    stream << "                                                                               \n";
    stream << "You should also get your employer (if you work as a programmer) or your        \n";
    stream << "school, if any, to sign a \"copyright disclaimer\" for the program, if         \n";
    stream << "necessary.  Here is a sample; alter the names:                                 \n";
    stream << "                                                                               \n";
    stream << "  Yoyodyne, Inc., hereby disclaims all copyright interest in the program       \n";
    stream << "  `Gnomovision' (which makes passes at compilers) written by James Hacker.     \n";
    stream << "                                                                               \n";
    stream << "  <signature of Ty Coon>, 1 April 1989                                         \n";
    stream << "  Ty Coon, President of Vice                                                   \n";
    stream << "                                                                               \n";
    stream << "This General Public License does not permit incorporating your program into    \n";
    stream << "proprietary programs.  If your program is a subroutine library, you may        \n";
    stream << "consider it more useful to permit linking proprietary applications with the    \n";
    stream << "library.  If this is what you want to do, use the GNU Lesser General           \n";
    stream << "Public License instead of this License.                                          ";
    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());
}


void USBTestCli::DisplayWarranty()
{
    std::stringstream stream;

    stream << "                NO WARRANTY                                                    \n";
    stream << "                                                                               \n";
    stream << "  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY     \n";
    stream << "FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN       \n";
    stream << "OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES         \n";
    stream << "PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED   \n";
    stream << "OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           \n";
    stream << "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS      \n";
    stream << "TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE         \n";
    stream << "PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,       \n";
    stream << "REPAIR OR CORRECTION.                                                          \n";
    stream << "                                                                               \n";
    stream << "  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING    \n";
    stream << "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR            \n";
    stream << "REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,     \n";
    stream << "INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING    \n";
    stream << "OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED      \n";
    stream << "TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY       \n";
    stream << "YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER     \n";
    stream << "PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE          \n";
    stream << "POSSIBILITY OF SUCH DAMAGES.                                                     ";
    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());
}
