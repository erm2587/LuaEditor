/*	Copyright (c) 2015 SGH
**	
**	Permission is granted to use, modify and redistribute this software.
**	Modified versions of this software MUST be marked as such.
**	
**	This software is provided "AS IS". In no event shall
**	the authors or copyright holders be liable for any claim,
**	damages or other liability. The above copyright notice
**	and this permission notice shall be included in all copies
**	or substantial portions of the software.
**	
**	File created on: 23/08/2015
*/

#ifndef LUACOMPLETIONASSISTPROCESSOR_H
#define LUACOMPLETIONASSISTPROCESSOR_H
#include "luaeditor_global.h"
#include "luafunctionhintproposalmodel.h"
#include <texteditor/codeassist/iassistprocessor.h>
#include <QIcon>
#include <QString>
#include <QMap>

namespace TextEditor {
class GenericProposal;
}

namespace LuaEditor { namespace Internal {

class LuaCompletionAssistProcessor : public TextEditor::IAssistProcessor
{
public:
    typedef LuaFunctionHintProposalModel::Function Function;

public:
	LuaCompletionAssistProcessor();
	virtual ~LuaCompletionAssistProcessor();
	TextEditor::IAssistProposal* perform(TextEditor::AssistInterface const* interface);
	virtual bool acceptsIdleEditor() const;
	
	int m_startPosition;
	
	QIcon m_varIcon;
	QIcon m_functionIcon;
	QIcon m_memIcon;
	QIcon m_keywordIcon;

    QStringList predefinedMembers;
    QStringList predefinedCalls;
    QStringList predefinedWords;
    QMap<QString, QVector<Function>> predefinedFunctionInfosByFunction;
    QMap<QString, QVector<Function>> predefinedFunctionInfosByObject;
    QMap<QString, QStringList> predefinedMemberInfos;

    void readWords(QStringList &out, QString path);
    void readCalls(QStringList &words, QMap<QString, QVector<Function>> &functionsByFunction, QMap<QString, QVector<Function>> &functionsByObject, QString path);
    void readMembers(QStringList &words, QMap<QString, QStringList> &members, QString path);

    TextEditor::GenericProposal *createContentProposal(const TextEditor::AssistInterface *interface);
    TextEditor::IAssistProposal *tryCreateFunctionHintProposal(const TextEditor::AssistInterface *interface);
};

} }
#endif // LUACOMPLETIONASSISTPROCESSOR_H
