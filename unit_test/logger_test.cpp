#include <cstdlib>
#include <string>

#include <gtest/gtest.h>

#include <QByteArray>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "logger.h"


void removeFile (const QString &filename)
{
  QString command = "rm " + filename;
  QByteArray byteArray = command.toLocal8Bit();
  std::system(byteArray.data());
}

TEST(Logger, write)
{
  Logger logger;
  QString filename = "testFile.txt";
  logger.write ("This is a test", filename);

  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly))
  {
      return;
  }

  QTextStream instream(&file);
  QString line = instream.readLine();

  EXPECT_EQ(line,"This is a test");
  file.close();

  removeFile (filename);
}

TEST(Logger, writeHTMLSourceToFile)
{
  Logger logger;
  QString filename = "testFile.txt";
  logger.writeHTMLSourceToFile (filename, "This is a test");

  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly))
  {
      return;
  }

  QTextStream instream(&file);
  QString line = instream.readLine();

  EXPECT_EQ(line,"This is a test");
  file.close();

  removeFile (filename);
}
