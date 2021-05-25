#pragma once
#ifndef PALETTES_H
#define PALETTES_H

#include <QColor>
#include <QStringList>
#include <vector>
#include <map>

namespace PALETTES{
    const std::vector<QColor> ERROR{
        QColor(0,0,0,0)
    };

    const std::vector<QColor> DOOM{
        QColor(0,0,0),
        QColor(31,23,11),
        QColor(23,15,7),
        QColor(75,75,75),
        QColor(255,255,255),
        QColor(27,27,27),
        QColor(19,19,19),
        QColor(11,11,11),
        QColor(7,7,7),
        QColor(47,55,31),
        QColor(35,43,15),
        QColor(23,31,7),
        QColor(15,23,0),
        QColor(79,59,43),
        QColor(71,51,35),
        QColor(63,43,27),
        QColor(255,183,183),
        QColor(247,171,171),
        QColor(243,163,163),
        QColor(235,151,151),
        QColor(231,143,143),
        QColor(223,135,135),
        QColor(219,123,123),
        QColor(211,115,115),
        QColor(203,107,107),
        QColor(199,99,99),
        QColor(191,91,91),
        QColor(187,87,87),
        QColor(179,79,79),
        QColor(175,71,71),
        QColor(167,63,63),
        QColor(163,59,59),
        QColor(155,51,51),
        QColor(151,47,47),
        QColor(143,43,43),
        QColor(139,35,35),
        QColor(131,31,31),
        QColor(127,27,27),
        QColor(119,23,23),
        QColor(115,19,19),
        QColor(107,15,15),
        QColor(103,11,11),
        QColor(95,7,7),
        QColor(91,7,7),
        QColor(83,7,7),
        QColor(79,0,0),
        QColor(71,0,0),
        QColor(67,0,0),
        QColor(255,235,223),
        QColor(255,227,211),
        QColor(255,219,199),
        QColor(255,211,187),
        QColor(255,207,179),
        QColor(255,199,167),
        QColor(255,191,155),
        QColor(255,187,147),
        QColor(255,179,131),
        QColor(247,171,123),
        QColor(239,163,115),
        QColor(231,155,107),
        QColor(223,147,99),
        QColor(215,139,91),
        QColor(207,131,83),
        QColor(203,127,79),
        QColor(191,123,75),
        QColor(179,115,71),
        QColor(171,111,67),
        QColor(163,107,63),
        QColor(155,99,59),
        QColor(143,95,55),
        QColor(135,87,51),
        QColor(127,83,47),
        QColor(119,79,43),
        QColor(107,71,39),
        QColor(95,67,35),
        QColor(83,63,31),
        QColor(75,55,27),
        QColor(63,47,23),
        QColor(51,43,19),
        QColor(43,35,15),
        QColor(239,239,239),
        QColor(231,231,231),
        QColor(223,223,223),
        QColor(219,219,219),
        QColor(211,211,211),
        QColor(203,203,203),
        QColor(199,199,199),
        QColor(191,191,191),
        QColor(183,183,183),
        QColor(179,179,179),
        QColor(171,171,171),
        QColor(167,167,167),
        QColor(159,159,159),
        QColor(151,151,151),
        QColor(147,147,147),
        QColor(139,139,139),
        QColor(131,131,131),
        QColor(127,127,127),
        QColor(119,119,119),
        QColor(111,111,111),
        QColor(107,107,107),
        QColor(99,99,99),
        QColor(91,91,91),
        QColor(87,87,87),
        QColor(79,79,79),
        QColor(71,71,71),
        QColor(67,67,67),
        QColor(59,59,59),
        QColor(55,55,55),
        QColor(47,47,47),
        QColor(39,39,39),
        QColor(35,35,35),
        QColor(119,255,111),
        QColor(111,239,103),
        QColor(103,223,95),
        QColor(95,207,87),
        QColor(91,191,79),
        QColor(83,175,71),
        QColor(75,159,63),
        QColor(67,147,55),
        QColor(63,131,47),
        QColor(55,115,43),
        QColor(47,99,35),
        QColor(39,83,27),
        QColor(31,67,23),
        QColor(23,51,15),
        QColor(19,35,11),
        QColor(11,23,7),
        QColor(191,167,143),
        QColor(183,159,135),
        QColor(175,151,127),
        QColor(167,143,119),
        QColor(159,135,111),
        QColor(155,127,107),
        QColor(147,123,99),
        QColor(139,115,91),
        QColor(131,107,87),
        QColor(123,99,79),
        QColor(119,95,75),
        QColor(111,87,67),
        QColor(103,83,63),
        QColor(95,75,55),
        QColor(87,67,51),
        QColor(83,63,47),
        QColor(159,131,99),
        QColor(143,119,83),
        QColor(131,107,75),
        QColor(119,95,63),
        QColor(103,83,51),
        QColor(91,71,43),
        QColor(79,59,35),
        QColor(67,51,27),
        QColor(123,127,99),
        QColor(111,115,87),
        QColor(103,107,79),
        QColor(91,99,71),
        QColor(83,87,59),
        QColor(71,79,51),
        QColor(63,71,43),
        QColor(55,63,39),
        QColor(255,255,115),
        QColor(235,219,87),
        QColor(215,187,67),
        QColor(195,155,47),
        QColor(175,123,31),
        QColor(155,91,19),
        QColor(135,67,7),
        QColor(115,43,0),
        QColor(255,219,219),
        QColor(255,187,187),
        QColor(255,155,155),
        QColor(255,123,123),
        QColor(255,95,95),
        QColor(255,63,63),
        QColor(255,31,31),
        QColor(255,0,0),
        QColor(239,0,0),
        QColor(227,0,0),
        QColor(215,0,0),
        QColor(203,0,0),
        QColor(191,0,0),
        QColor(179,0,0),
        QColor(167,0,0),
        QColor(155,0,0),
        QColor(139,0,0),
        QColor(127,0,0),
        QColor(115,0,0),
        QColor(103,0,0),
        QColor(91,0,0),
        QColor(231,231,255),
        QColor(199,199,255),
        QColor(171,171,255),
        QColor(143,143,255),
        QColor(115,115,255),
        QColor(83,83,255),
        QColor(55,55,255),
        QColor(27,27,255),
        QColor(0,0,255),
        QColor(0,0,227),
        QColor(0,0,203),
        QColor(0,0,179),
        QColor(0,0,155),
        QColor(0,0,131),
        QColor(0,0,107),
        QColor(0,0,83),
        QColor(255,235,219),
        QColor(255,215,187),
        QColor(255,199,155),
        QColor(255,179,123),
        QColor(255,163,91),
        QColor(255,143,59),
        QColor(255,127,27),
        QColor(243,115,23),
        QColor(235,111,15),
        QColor(223,103,15),
        QColor(215,95,11),
        QColor(203,87,7),
        QColor(195,79,0),
        QColor(183,71,0),
        QColor(175,67,0),
        QColor(255,255,215),
        QColor(255,255,179),
        QColor(255,255,143),
        QColor(255,255,107),
        QColor(255,255,71),
        QColor(255,255,35),
        QColor(255,255,0),
        QColor(167,63,0),
        QColor(159,55,0),
        QColor(147,47,0),
        QColor(135,35,0),
        QColor(79,59,39),
        QColor(67,47,27),
        QColor(55,35,19),
        QColor(47,27,11),
        QColor(0,0,71),
        QColor(0,0,59),
        QColor(0,0,47),
        QColor(0,0,35),
        QColor(0,0,23),
        QColor(0,0,11),
        QColor(255,159,67),
        QColor(255,231,75),
        QColor(255,123,255),
        QColor(255,0,255),
        QColor(207,0,207),
        QColor(159,0,155),
        QColor(111,0,107),
        QColor(167,107,107)
    };

    const std::vector<QColor> QUAKE{
        QColor(0,0,0),
        QColor(15,15,15),
        QColor(31,31,31),
        QColor(47,47,47),
        QColor(63,63,63),
        QColor(75,75,75),
        QColor(91,91,91),
        QColor(107,107,107),
        QColor(123,123,123),
        QColor(139,139,139),
        QColor(155,155,155),
        QColor(171,171,171),
        QColor(187,187,187),
        QColor(203,203,203),
        QColor(219,219,219),
        QColor(235,235,235),
        QColor(15,11,7),
        QColor(23,15,11),
        QColor(31,23,11),
        QColor(39,27,15),
        QColor(47,35,19),
        QColor(55,43,23),
        QColor(63,47,23),
        QColor(75,55,27),
        QColor(83,59,27),
        QColor(91,67,31),
        QColor(99,75,31),
        QColor(107,83,31),
        QColor(115,87,31),
        QColor(123,95,35),
        QColor(131,103,35),
        QColor(143,111,35),
        QColor(11,11,15),
        QColor(19,19,27),
        QColor(27,27,39),
        QColor(39,39,51),
        QColor(47,47,63),
        QColor(55,55,75),
        QColor(63,63,87),
        QColor(71,71,103),
        QColor(79,79,115),
        QColor(91,91,127),
        QColor(99,99,139),
        QColor(107,107,151),
        QColor(115,115,163),
        QColor(123,123,175),
        QColor(131,131,187),
        QColor(139,139,203),
        QColor(7,7,0),
        QColor(11,11,0),
        QColor(19,19,0),
        QColor(27,27,0),
        QColor(35,35,0),
        QColor(43,43,7),
        QColor(47,47,7),
        QColor(55,55,7),
        QColor(63,63,7),
        QColor(71,71,7),
        QColor(75,75,11),
        QColor(83,83,11),
        QColor(91,91,11),
        QColor(99,99,11),
        QColor(107,107,15),
        QColor(7,0,0),
        QColor(15,0,0),
        QColor(23,0,0),
        QColor(31,0,0),
        QColor(39,0,0),
        QColor(47,0,0),
        QColor(55,0,0),
        QColor(63,0,0),
        QColor(71,0,0),
        QColor(79,0,0),
        QColor(87,0,0),
        QColor(95,0,0),
        QColor(103,0,0),
        QColor(111,0,0),
        QColor(119,0,0),
        QColor(127,0,0),
        QColor(47,43,0),
        QColor(55,47,0),
        QColor(67,55,0),
        QColor(75,59,7),
        QColor(87,67,7),
        QColor(95,71,7),
        QColor(107,75,11),
        QColor(119,83,15),
        QColor(131,87,19),
        QColor(139,91,19),
        QColor(151,95,27),
        QColor(163,99,31),
        QColor(175,103,35),
        QColor(35,19,7),
        QColor(47,23,11),
        QColor(59,31,15),
        QColor(75,35,19),
        QColor(87,43,23),
        QColor(99,47,31),
        QColor(115,55,35),
        QColor(127,59,43),
        QColor(143,67,51),
        QColor(159,79,51),
        QColor(175,99,47),
        QColor(191,119,47),
        QColor(207,143,43),
        QColor(223,171,39),
        QColor(239,203,31),
        QColor(255,243,27),
        QColor(11,7,0),
        QColor(27,19,0),
        QColor(43,35,15),
        QColor(55,43,19),
        QColor(71,51,27),
        QColor(83,55,35),
        QColor(99,63,43),
        QColor(111,71,51),
        QColor(127,83,63),
        QColor(139,95,71),
        QColor(155,107,83),
        QColor(167,123,95),
        QColor(183,135,107),
        QColor(195,147,123),
        QColor(211,163,139),
        QColor(227,179,151),
        QColor(171,139,163),
        QColor(159,127,151),
        QColor(147,115,135),
        QColor(139,103,123),
        QColor(127,91,111),
        QColor(119,83,99),
        QColor(107,75,87),
        QColor(95,63,75),
        QColor(87,55,67),
        QColor(75,47,55),
        QColor(67,39,47),
        QColor(55,31,35),
        QColor(43,23,27),
        QColor(35,19,19),
        QColor(23,11,11),
        QColor(15,7,7),
        QColor(187,115,159),
        QColor(175,107,143),
        QColor(163,95,131),
        QColor(151,87,119),
        QColor(139,79,107),
        QColor(127,75,95),
        QColor(115,67,83),
        QColor(107,59,75),
        QColor(95,51,63),
        QColor(83,43,55),
        QColor(71,35,43),
        QColor(59,31,35),
        QColor(47,23,27),
        QColor(219,195,187),
        QColor(203,179,167),
        QColor(191,163,155),
        QColor(175,151,139),
        QColor(163,135,123),
        QColor(151,123,111),
        QColor(135,111,95),
        QColor(123,99,83),
        QColor(107,87,71),
        QColor(95,75,59),
        QColor(83,63,51),
        QColor(67,51,39),
        QColor(55,43,31),
        QColor(39,31,23),
        QColor(27,19,15),
        QColor(111,131,123),
        QColor(103,123,111),
        QColor(95,115,103),
        QColor(87,107,95),
        QColor(79,99,87),
        QColor(71,91,79),
        QColor(63,83,71),
        QColor(55,75,63),
        QColor(47,67,55),
        QColor(43,59,47),
        QColor(35,51,39),
        QColor(31,43,31),
        QColor(23,35,23),
        QColor(15,27,19),
        QColor(11,19,11),
        QColor(7,11,7),
        QColor(239,223,23),
        QColor(219,203,19),
        QColor(203,183,15),
        QColor(187,167,15),
        QColor(171,151,11),
        QColor(155,131,7),
        QColor(139,115,7),
        QColor(123,99,7),
        QColor(107,83,0),
        QColor(91,71,0),
        QColor(75,55,0),
        QColor(59,43,0),
        QColor(43,31,0),
        QColor(27,15,0),
        QColor(0,0,255),
        QColor(11,11,239),
        QColor(19,19,223),
        QColor(27,27,207),
        QColor(35,35,191),
        QColor(43,43,175),
        QColor(47,47,159),
        QColor(47,47,143),
        QColor(47,47,127),
        QColor(47,47,111),
        QColor(47,47,95),
        QColor(43,43,79),
        QColor(35,35,63),
        QColor(27,27,47),
        QColor(19,19,31),
        QColor(43,0,0),
        QColor(59,0,0),
        QColor(75,7,0),
        QColor(95,7,0),
        QColor(111,15,0),
        QColor(127,23,7),
        QColor(147,31,7),
        QColor(163,39,11),
        QColor(183,51,15),
        QColor(195,75,27),
        QColor(207,99,43),
        QColor(219,127,59),
        QColor(227,151,79),
        QColor(231,171,95),
        QColor(239,191,119),
        QColor(247,211,139),
        QColor(167,123,59),
        QColor(183,155,55),
        QColor(199,195,55),
        QColor(231,227,87),
        QColor(127,191,255),
        QColor(171,231,255),
        QColor(215,255,255),
        QColor(139,0,0),
        QColor(179,0,0),
        QColor(215,0,0),
        QColor(255,0,0),
        QColor(255,243,147),
        QColor(255,247,199),
        QColor(255,255,255),
        QColor(159,91,83)
    };
};

const QStringList HARD_PALETTE_NAMES = {
    "DOOM",
    "QUAKE"
};

const std::map<int,const std::vector<QColor>*> HARD_PALETTES = {
    {0, &PALETTES::DOOM},
    {1, &PALETTES::QUAKE}
};

#endif