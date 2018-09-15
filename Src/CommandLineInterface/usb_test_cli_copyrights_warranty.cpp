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

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"


/* **************************************************************************************************** */
/* ********************************** Display CopyRights and Warraty ********************************** */
/* **************************************************************************************************** */


void USBTestCli::DisplayCopyRights()
{
    std::cout << std::endl;
    std::cout << "	            GNU GENERAL PUBLIC LICENSE                                              "<< std::endl;
    std::cout << "	               Version 2, June 1991                                                 "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "Copyright (C) 1989, 1991 Free Software Foundation, Inc.,                              "<< std::endl;
    std::cout << "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA                            "<< std::endl;
    std::cout << "Everyone is permitted to copy and distribute verbatim copies                          "<< std::endl;
    std::cout << "of this license document, but changing it is not allowed.                             "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "                      Preamble                                                        "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  The licenses for most software are designed to take away your                       "<< std::endl;
    std::cout << "freedom to share and change it.  By contrast, the GNU General Public                  "<< std::endl;
    std::cout << "License is intended to guarantee your freedom to share and change free                "<< std::endl;
    std::cout << "software--to make sure the software is free for all its users.  This                  "<< std::endl;
    std::cout << "General Public License applies to most of the Free Software                           "<< std::endl;
    std::cout << "Foundation's software and to any other program whose authors commit to                "<< std::endl;
    std::cout << "using it.  (Some other Free Software Foundation software is covered by                "<< std::endl;
    std::cout << "the GNU Lesser General Public License instead.)  You can apply it to                  "<< std::endl;
    std::cout << "your programs, too.                                                                   "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  When we speak of free software, we are referring to freedom, not                    "<< std::endl;
    std::cout << "price.  Our General Public Licenses are designed to make sure that you                "<< std::endl;
    std::cout << "have the freedom to distribute copies of free software (and charge for                "<< std::endl;
    std::cout << "this service if you wish), that you receive source code or can get it                 "<< std::endl;
    std::cout << "if you want it, that you can change the software or use pieces of it                  "<< std::endl;
    std::cout << "in new free programs; and that you know you can do these things.                      "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  To protect your rights, we need to make restrictions that forbid                    "<< std::endl;
    std::cout << "anyone to deny you these rights or to ask you to surrender the rights.                "<< std::endl;
    std::cout << "These restrictions translate to certain responsibilities for you if you               "<< std::endl;
    std::cout << "distribute copies of the software, or if you modify it.                               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  For example, if you distribute copies of such a program, whether                    "<< std::endl;
    std::cout << "gratis or for a fee, you must give the recipients all the rights that                 "<< std::endl;
    std::cout << "you have.  You must make sure that they, too, receive or can get the                  "<< std::endl;
    std::cout << "source code.  And you must show them these terms so they know their                   "<< std::endl;
    std::cout << "rights.                                                                               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  We protect your rights with two steps: (1) copyright the software, and              "<< std::endl;
    std::cout << "(2) offer you this license which gives you legal permission to copy,                  "<< std::endl;
    std::cout << "distribute and/or modify the software.                                                "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  Also, for each author's protection and ours, we want to make certain                "<< std::endl;
    std::cout << "that everyone understands that there is no warranty for this free                     "<< std::endl;
    std::cout << "software.  If the software is modified by someone else and passed on, we              "<< std::endl;
    std::cout << "want its recipients to know that what they have is not the original, so               "<< std::endl;
    std::cout << "that any problems introduced by others will not reflect on the original               "<< std::endl;
    std::cout << "authors' reputations.                                                                 "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  Finally, any free program is threatened constantly by software                      "<< std::endl;
    std::cout << "patents.  We wish to avoid the danger that redistributors of a free                   "<< std::endl;
    std::cout << "program will individually obtain patent licenses, in effect making the                "<< std::endl;
    std::cout << "program proprietary.  To prevent this, we have made it clear that any                 "<< std::endl;
    std::cout << "patent must be licensed for everyone's free use or not licensed at all.               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  The precise terms and conditions for copying, distribution and                      "<< std::endl;
    std::cout << "modification follow.                                                                  "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "              GNU GENERAL PUBLIC LICENSE                                              "<< std::endl;
    std::cout << "     TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION                  "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  0. This License applies to any program or other work which contains                 "<< std::endl;
    std::cout << "a notice placed by the copyright holder saying it may be distributed                  "<< std::endl;
    std::cout << "under the terms of this General Public License.  The \"Program\", below,              "<< std::endl;
    std::cout << "refers to any such program or work, and a \"work based on the Program\"               "<< std::endl;
    std::cout << "means either the Program or any derivative work under copyright law:                  "<< std::endl;
    std::cout << "that is to say, a work containing the Program or a portion of it,                     "<< std::endl;
    std::cout << "either verbatim or with modifications and/or translated into another                  "<< std::endl;
    std::cout << "language.  (Hereinafter, translation is included without limitation in                "<< std::endl;
    std::cout << "the term \"modification\".)  Each licensee is addressed as \"you\".                   "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "Activities other than copying, distribution and modification are not                  "<< std::endl;
    std::cout << "covered by this License; they are outside its scope.  The act of                      "<< std::endl;
    std::cout << "running the Program is not restricted, and the output from the Program                "<< std::endl;
    std::cout << "is covered only if its contents constitute a work based on the                        "<< std::endl;
    std::cout << "Program (independent of having been made by running the Program).                     "<< std::endl;
    std::cout << "Whether that is true depends on what the Program does.                                "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  1. You may copy and distribute verbatim copies of the Program's                     "<< std::endl;
    std::cout << "source code as you receive it, in any medium, provided that you                       "<< std::endl;
    std::cout << "conspicuously and appropriately publish on each copy an appropriate                   "<< std::endl;
    std::cout << "copyright notice and disclaimer of warranty; keep intact all the                      "<< std::endl;
    std::cout << "notices that refer to this License and to the absence of any warranty;                "<< std::endl;
    std::cout << "and give any other recipients of the Program a copy of this License                   "<< std::endl;
    std::cout << "along with the Program.                                                               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "You may charge a fee for the physical act of transferring a copy, and                 "<< std::endl;
    std::cout << "you may at your option offer warranty protection in exchange for a fee.               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  2. You may modify your copy or copies of the Program or any portion                 "<< std::endl;
    std::cout << "of it, thus forming a work based on the Program, and copy and                         "<< std::endl;
    std::cout << "distribute such modifications or work under the terms of Section 1                    "<< std::endl;
    std::cout << "above, provided that you also meet all of these conditions:                           "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "      a) You must cause the modified files to carry prominent notices                 "<< std::endl;
    std::cout << "      stating that you changed the files and the date of any change.                  "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "      b) You must cause any work that you distribute or publish, that in              "<< std::endl;
    std::cout << "      whole or in part contains or is derived from the Program or any                 "<< std::endl;
    std::cout << "      part thereof, to be licensed as a whole at no charge to all third               "<< std::endl;
    std::cout << "      parties under the terms of this License.                                        "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "      c) If the modified program normally reads commands interactively                "<< std::endl;
    std::cout << "      when run, you must cause it, when started running for such                      "<< std::endl;
    std::cout << "      interactive use in the most ordinary way, to print or display an                "<< std::endl;
    std::cout << "      announcement including an appropriate copyright notice and a                    "<< std::endl;
    std::cout << "      notice that there is no warranty (or else, saying that you provide              "<< std::endl;
    std::cout << "      a warranty) and that users may redistribute the program under                   "<< std::endl;
    std::cout << "      these conditions, and telling the user how to view a copy of this               "<< std::endl;
    std::cout << "      License.  (Exception: if the Program itself is interactive but                  "<< std::endl;
    std::cout << "      does not normally print such an announcement, your work based on                "<< std::endl;
    std::cout << "      the Program is not required to print an announcement.)                          "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "These requirements apply to the modified work as a whole.  If                         "<< std::endl;
    std::cout << "identifiable sections of that work are not derived from the Program,                  "<< std::endl;
    std::cout << "and can be reasonably considered independent and separate works in                    "<< std::endl;
    std::cout << "themselves, then this License, and its terms, do not apply to those                   "<< std::endl;
    std::cout << "sections when you distribute them as separate works.  But when you                    "<< std::endl;
    std::cout << "distribute the same sections as part of a whole which is a work based                 "<< std::endl;
    std::cout << "on the Program, the distribution of the whole must be on the terms of                 "<< std::endl;
    std::cout << "this License, whose permissions for other licensees extend to the                     "<< std::endl;
    std::cout << "entire whole, and thus to each and every part regardless of who wrote it.             "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "Thus, it is not the intent of this section to claim rights or contest                 "<< std::endl;
    std::cout << "your rights to work written entirely by you; rather, the intent is to                 "<< std::endl;
    std::cout << "exercise the right to control the distribution of derivative or                       "<< std::endl;
    std::cout << "collective works based on the Program.                                                "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "In addition, mere aggregation of another work not based on the Program                "<< std::endl;
    std::cout << "with the Program (or with a work based on the Program) on a volume of                 "<< std::endl;
    std::cout << "a storage or distribution medium does not bring the other work under                  "<< std::endl;
    std::cout << "the scope of this License.                                                            "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  3. You may copy and distribute the Program (or a work based on it,                  "<< std::endl;
    std::cout << "under Section 2) in object code or executable form under the terms of                 "<< std::endl;
    std::cout << "Sections 1 and 2 above provided that you also do one of the following:                "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "      a) Accompany it with the complete corresponding machine-readable                "<< std::endl;
    std::cout << "      source code, which must be distributed under the terms of Sections              "<< std::endl;
    std::cout << "      1 and 2 above on a medium customarily used for software interchange; or,        "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "      b) Accompany it with a written offer, valid for at least three                  "<< std::endl;
    std::cout << "      years, to give any third party, for a charge no more than your                  "<< std::endl;
    std::cout << "      cost of physically performing source distribution, a complete                   "<< std::endl;
    std::cout << "      machine-readable copy of the corresponding source code, to be                   "<< std::endl;
    std::cout << "      distributed under the terms of Sections 1 and 2 above on a medium               "<< std::endl;
    std::cout << "      customarily used for software interchange; or,                                  "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "      c) Accompany it with the information you received as to the offer               "<< std::endl;
    std::cout << "      to distribute corresponding source code.  (This alternative is                  "<< std::endl;
    std::cout << "      allowed only for noncommercial distribution and only if you                     "<< std::endl;
    std::cout << "      received the program in object code or executable form with such                "<< std::endl;
    std::cout << "      an offer, in accord with Subsection b above.)                                   "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "The source code for a work means the preferred form of the work for                   "<< std::endl;
    std::cout << "making modifications to it.  For an executable work, complete source                  "<< std::endl;
    std::cout << "code means all the source code for all modules it contains, plus any                  "<< std::endl;
    std::cout << "associated interface definition files, plus the scripts used to                       "<< std::endl;
    std::cout << "control compilation and installation of the executable.  However, as a                "<< std::endl;
    std::cout << "special exception, the source code distributed need not include                       "<< std::endl;
    std::cout << "anything that is normally distributed (in either source or binary                     "<< std::endl;
    std::cout << "form) with the major components (compiler, kernel, and so on) of the                  "<< std::endl;
    std::cout << "operating system on which the executable runs, unless that component                  "<< std::endl;
    std::cout << "itself accompanies the executable.                                                    "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "If distribution of executable or object code is made by offering                      "<< std::endl;
    std::cout << "access to copy from a designated place, then offering equivalent                      "<< std::endl;
    std::cout << "access to copy the source code from the same place counts as                          "<< std::endl;
    std::cout << "distribution of the source code, even though third parties are not                    "<< std::endl;
    std::cout << "compelled to copy the source along with the object code.                              "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  4. You may not copy, modify, sublicense, or distribute the Program                  "<< std::endl;
    std::cout << "except as expressly provided under this License.  Any attempt                         "<< std::endl;
    std::cout << "otherwise to copy, modify, sublicense or distribute the Program is                    "<< std::endl;
    std::cout << "void, and will automatically terminate your rights under this License.                "<< std::endl;
    std::cout << "However, parties who have received copies, or rights, from you under                  "<< std::endl;
    std::cout << "this License will not have their licenses terminated so long as such                  "<< std::endl;
    std::cout << "parties remain in full compliance.                                                    "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  5. You are not required to accept this License, since you have not                  "<< std::endl;
    std::cout << "signed it.  However, nothing else grants you permission to modify or                  "<< std::endl;
    std::cout << "distribute the Program or its derivative works.  These actions are                    "<< std::endl;
    std::cout << "prohibited by law if you do not accept this License.  Therefore, by                   "<< std::endl;
    std::cout << "modifying or distributing the Program (or any work based on the                       "<< std::endl;
    std::cout << "Program), you indicate your acceptance of this License to do so, and                  "<< std::endl;
    std::cout << "all its terms and conditions for copying, distributing or modifying                   "<< std::endl;
    std::cout << "the Program or works based on it.                                                     "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  6. Each time you redistribute the Program (or any work based on the                 "<< std::endl;
    std::cout << "Program), the recipient automatically receives a license from the                     "<< std::endl;
    std::cout << "original licensor to copy, distribute or modify the Program subject to                "<< std::endl;
    std::cout << "these terms and conditions.  You may not impose any further                           "<< std::endl;
    std::cout << "restrictions on the recipients' exercise of the rights granted herein.                "<< std::endl;
    std::cout << "You are not responsible for enforcing compliance by third parties to                  "<< std::endl;
    std::cout << "this License.                                                                         "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  7. If, as a consequence of a court judgment or allegation of patent                 "<< std::endl;
    std::cout << "infringement or for any other reason (not limited to patent issues),                  "<< std::endl;
    std::cout << "conditions are imposed on you (whether by court order, agreement or                   "<< std::endl;
    std::cout << "otherwise) that contradict the conditions of this License, they do not                "<< std::endl;
    std::cout << "excuse you from the conditions of this License.  If you cannot                        "<< std::endl;
    std::cout << "distribute so as to satisfy simultaneously your obligations under this                "<< std::endl;
    std::cout << "License and any other pertinent obligations, then as a consequence you                "<< std::endl;
    std::cout << "may not distribute the Program at all.  For example, if a patent                      "<< std::endl;
    std::cout << "license would not permit royalty-free redistribution of the Program by                "<< std::endl;
    std::cout << "all those who receive copies directly or indirectly through you, then                 "<< std::endl;
    std::cout << "the only way you could satisfy both it and this License would be to                   "<< std::endl;
    std::cout << "refrain entirely from distribution of the Program.                                    "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "If any portion of this section is held invalid or unenforceable under                 "<< std::endl;
    std::cout << "any particular circumstance, the balance of the section is intended to                "<< std::endl;
    std::cout << "apply and the section as a whole is intended to apply in other                        "<< std::endl;
    std::cout << "circumstances.                                                                        "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "It is not the purpose of this section to induce you to infringe any                   "<< std::endl;
    std::cout << "patents or other property right claims or to contest validity of any                  "<< std::endl;
    std::cout << "such claims; this section has the sole purpose of protecting the                      "<< std::endl;
    std::cout << "integrity of the free software distribution system, which is                          "<< std::endl;
    std::cout << "implemented by public license practices.  Many people have made                       "<< std::endl;
    std::cout << "generous contributions to the wide range of software distributed                      "<< std::endl;
    std::cout << "through that system in reliance on consistent application of that                     "<< std::endl;
    std::cout << "system; it is up to the author/donor to decide if he or she is willing                "<< std::endl;
    std::cout << "to distribute software through any other system and a licensee cannot                 "<< std::endl;
    std::cout << "impose that choice.                                                                   "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "This section is intended to make thoroughly clear what is believed to                 "<< std::endl;
    std::cout << "be a consequence of the rest of this License.                                         "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  8. If the distribution and/or use of the Program is restricted in                   "<< std::endl;
    std::cout << "certain countries either by patents or by copyrighted interfaces, the                 "<< std::endl;
    std::cout << "original copyright holder who places the Program under this License                   "<< std::endl;
    std::cout << "may add an explicit geographical distribution limitation excluding                    "<< std::endl;
    std::cout << "those countries, so that distribution is permitted only in or among                   "<< std::endl;
    std::cout << "countries not thus excluded.  In such case, this License incorporates                 "<< std::endl;
    std::cout << "the limitation as if written in the body of this License.                             "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  9. The Free Software Foundation may publish revised and/or new versions             "<< std::endl;
    std::cout << "of the General Public License from time to time.  Such new versions will              "<< std::endl;
    std::cout << "be similar in spirit to the present version, but may differ in detail to              "<< std::endl;
    std::cout << "address new problems or concerns.                                                     "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "Each version is given a distinguishing version number.  If the Program                "<< std::endl;
    std::cout << "specifies a version number of this License which applies to it and \"any              "<< std::endl;
    std::cout << "later version\", you have the option of following the terms and conditions            "<< std::endl;
    std::cout << "either of that version or of any later version published by the Free                  "<< std::endl;
    std::cout << "Software Foundation.  If the Program does not specify a version number of             "<< std::endl;
    std::cout << "this License, you may choose any version ever published by the Free Software          "<< std::endl;
    std::cout << "Foundation.                                                                           "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  10. If you wish to incorporate parts of the Program into other free                 "<< std::endl;
    std::cout << "programs whose distribution conditions are different, write to the author             "<< std::endl;
    std::cout << "to ask for permission.  For software which is copyrighted by the Free                 "<< std::endl;
    std::cout << "Software Foundation, write to the Free Software Foundation; we sometimes              "<< std::endl;
    std::cout << "make exceptions for this.  Our decision will be guided by the two goals               "<< std::endl;
    std::cout << "of preserving the free status of all derivatives of our free software and             "<< std::endl;
    std::cout << "of promoting the sharing and reuse of software generally.                             "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "                NO WARRANTY                                                           "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY            "<< std::endl;
    std::cout << "FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN              "<< std::endl;
    std::cout << "OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES                "<< std::endl;
    std::cout << "PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED          "<< std::endl;
    std::cout << "OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF                  "<< std::endl;
    std::cout << "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS             "<< std::endl;
    std::cout << "TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE                "<< std::endl;
    std::cout << "PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,              "<< std::endl;
    std::cout << "REPAIR OR CORRECTION.                                                                 "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING           "<< std::endl;
    std::cout << "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR                   "<< std::endl;
    std::cout << "REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,            "<< std::endl;
    std::cout << "INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING           "<< std::endl;
    std::cout << "OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED             "<< std::endl;
    std::cout << "TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY              "<< std::endl;
    std::cout << "YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER            "<< std::endl;
    std::cout << "PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE                 "<< std::endl;
    std::cout << "POSSIBILITY OF SUCH DAMAGES.                                                          "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "             END OF TERMS AND CONDITIONS                                              "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "        How to Apply These Terms to Your New Programs                                 "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  If you develop a new program, and you want it to be of the greatest                 "<< std::endl;
    std::cout << "possible use to the public, the best way to achieve this is to make it                "<< std::endl;
    std::cout << "free software which everyone can redistribute and change under these terms.           "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  To do so, attach the following notices to the program.  It is safest                "<< std::endl;
    std::cout << "to attach them to the start of each source file to most effectively                   "<< std::endl;
    std::cout << "convey the exclusion of warranty; and each file should have at least                  "<< std::endl;
    std::cout << "the \"copyright\" line and a pointer to where the full notice is found.               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "    <one line to give the program's name and a brief idea of what it does.>           "<< std::endl;
    std::cout << "    Copyright (C) <year>  <name of author>                                            "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "    This program is free software; you can redistribute it and/or modify              "<< std::endl;
    std::cout << "    it under the terms of the GNU General Public License as published by              "<< std::endl;
    std::cout << "    the Free Software Foundation; either version 2 of the License, or                 "<< std::endl;
    std::cout << "    (at your option) any later version.                                               "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "    This program is distributed in the hope that it will be useful,                   "<< std::endl;
    std::cout << "    but WITHOUT ANY WARRANTY; without even the implied warranty of                    "<< std::endl;
    std::cout << "    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                     "<< std::endl;
    std::cout << "    GNU General Public License for more details.                                      "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "    You should have received a copy of the GNU General Public License along           "<< std::endl;
    std::cout << "    with this program; if not, write to the Free Software Foundation, Inc.,           "<< std::endl;
    std::cout << "    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                       "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "Also add information on how to contact you by electronic and paper mail.              "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "If the program is interactive, make it output a short notice like this                "<< std::endl;
    std::cout << "when it starts in an interactive mode:                                                "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "    Gnomovision version 69, Copyright (C) year name of author                         "<< std::endl;
    std::cout << "    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.         "<< std::endl;
    std::cout << "    This is free software, and you are welcome to redistribute it                     "<< std::endl;
    std::cout << "    under certain conditions; type `show c' for details.                              "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "The hypothetical commands `show w' and `show c' should show the appropriate           "<< std::endl;
    std::cout << "parts of the General Public License.  Of course, the commands you use may             "<< std::endl;
    std::cout << "be called something other than `show w' and `show c'; they could even be              "<< std::endl;
    std::cout << "mouse-clicks or menu items--whatever suits your program.                              "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "You should also get your employer (if you work as a programmer) or your               "<< std::endl;
    std::cout << "school, if any, to sign a \"copyright disclaimer\" for the program, if                "<< std::endl;
    std::cout << "necessary.  Here is a sample; alter the names:                                        "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  Yoyodyne, Inc., hereby disclaims all copyright interest in the program              "<< std::endl;
    std::cout << "  `Gnomovision' (which makes passes at compilers) written by James Hacker.            "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  <signature of Ty Coon>, 1 April 1989                                                "<< std::endl;
    std::cout << "  Ty Coon, President of Vice                                                          "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "This General Public License does not permit incorporating your program into           "<< std::endl;
    std::cout << "proprietary programs.  If your program is a subroutine library, you may               "<< std::endl;
    std::cout << "consider it more useful to permit linking proprietary applications with the           "<< std::endl;
    std::cout << "library.  If this is what you want to do, use the GNU Lesser General                  "<< std::endl;
    std::cout << "Public License instead of this License.                                               "<< std::endl;
}


void USBTestCli::DisplayWarranty()
{
    std::cout << std::endl;
    std::cout << "                NO WARRANTY                                                           "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY            "<< std::endl;
    std::cout << "FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN              "<< std::endl;
    std::cout << "OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES                "<< std::endl;
    std::cout << "PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED          "<< std::endl;
    std::cout << "OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF                  "<< std::endl;
    std::cout << "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS             "<< std::endl;
    std::cout << "TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE                "<< std::endl;
    std::cout << "PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,              "<< std::endl;
    std::cout << "REPAIR OR CORRECTION.                                                                 "<< std::endl;
    std::cout << "                                                                                      "<< std::endl;
    std::cout << "  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING           "<< std::endl;
    std::cout << "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR                   "<< std::endl;
    std::cout << "REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,            "<< std::endl;
    std::cout << "INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING           "<< std::endl;
    std::cout << "OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED             "<< std::endl;
    std::cout << "TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY              "<< std::endl;
    std::cout << "YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER            "<< std::endl;
    std::cout << "PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE                 "<< std::endl;
    std::cout << "POSSIBILITY OF SUCH DAMAGES.                                                          "<< std::endl;
}
