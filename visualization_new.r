# same code in R language

library(tidyverse)
library(readxl)
library(ggplot2)
library(dplyr)
library(xlsx)

# data from all the sheets
sheet_names <- excel_sheets("C:\\Users\\jonte\\Downloads\\R Project\\poverty_by_characteristics_original.xlsx")

df <- lapply(sheet_names, function(x) read_excel("C:\\Users\\jonte\\Downloads\\R Project\\poverty_by_characteristics_original.xlsx", sheet = x))

# subplots for all the sheets in the excel file classifying by the year and column
for (i in 1:length(df)) {
  ggplot(df[[i]], aes(x = year, y = poverty_rate, fill = year)) +
    geom_bar(stat = "identity", position = "dodge") +
    facet_wrap(~characteristics, ncol = 2) +
    theme_bw() +
    theme(axis.text.x = element_text(angle = 90, hjust = 1)) +
    labs(title = "Poverty rate by characteristics", x = "Year", y = "Poverty")
}
