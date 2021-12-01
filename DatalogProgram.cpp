#include "DatalogProgram.h"
#include <sstream>
#include <iostream>
#include <algorithm>

DatalogProgram::DatalogProgram() {

}

DatalogProgram::~DatalogProgram() {
    /*for(unsigned int i = 0; i < schemes.size(); ++i){
        delete schemes.at(i);
    }
    for(unsigned int i = 0; i < facts.size(); ++i){
        delete facts.at(i);
    }
    for(unsigned int i = 0; i < queries.size(); ++i){
        delete queries.at(i);
    }
    for(unsigned int i = 0; i < rulePredicates.size(); ++i){
        delete rulePredicates.at(i);
    }
    for(unsigned int i = 0; i < rules.size(); ++i){
        delete rules.at(i);
    }
    for(unsigned int i = 0; i < tempParams.size(); ++i){
        delete tempParams.at(i);
    }*/
}

DatalogProgram::DatalogProgram(std::vector<Token*> tokenList) {
    this->tokenList = tokenList;
    tempText = "";
    tempID = "";
    index = 0;
}

void DatalogProgram::Init(DatalogProgram* self) {
    Datalog(self);
}

void DatalogProgram::Datalog(DatalogProgram* self) {
    //Schemes
    Match(TokenType::SCHEMES);
    parsingStage = ParsingStage::SCHEMES;
    Match(TokenType::COLON);
    tempText = "";
    Scheme();
    SchemeList();
    //Facts
    Match(TokenType::FACTS);
    parsingStage = ParsingStage::FACTS;
    Match(TokenType::COLON);
    tempText = "";
    FactList();
    //Rules
    Match(TokenType::RULES);
    parsingStage = ParsingStage::RULES;
    Match(TokenType::COLON);
    tempText = "";
    RuleList();
    //Queries
    Match(TokenType::QUERIES);
    parsingStage = ParsingStage::QUERIES;
    Match(TokenType::COLON);
    tempText = "";
    Query();
    QueryList();
    Match(TokenType::EOF_ENUM);
    //std::cout << "Success!" << std::endl;
    //testing
    FindDomain();
    //std::cout << DatalogToString();
}

void DatalogProgram::Match(TokenType tokenType) {
    tempText += tokenList.at(index)->GetDescription();
    if(tokenList.at(index)->GetType() == TokenType::ID || tokenList.at(index)->GetType() == TokenType::STRING) {
        tempID = "";
        tempID += tokenList.at(index)->GetDescription();
    }
    if(tokenList.at(index)->GetType() != tokenType){
        std::stringstream ss;
        std::string failure;
        ss << "Failure!" << std::endl << "  " << tokenList.at(index)->toString();
        failure = ss.str();
        throw failure;
    }
    index++;
}

void DatalogProgram::Scheme() {
    auto tempPredicate = new Predicates();
    auto tempParam = new Parameters();
    Match(TokenType::ID);
    tempPredicate->AddId(tempID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    tempParam->Setp(tempID);
    tempParams.push_back(tempParam);
    IdList();
    Match(TokenType::RIGHT_PAREN);
    tempPredicate->SetName(tempText);
    for (unsigned int i = 0; i < tempParams.size(); ++i){
        tempPredicate->AddParameter(tempParams.at(i));
    }
    schemes.push_back(tempPredicate);
    tempParams.clear();
    tempText = "";
}

void DatalogProgram::SchemeList() {
    if (tokenList.at(index)->GetType() == TokenType::FACTS){}
    // maybe need else if end of vector
    else{
        Scheme();
        SchemeList();
    }
}

void DatalogProgram::Fact() {
    auto tempPredicate = new Predicates();
    auto tempParam = new Parameters();
    Match(TokenType::ID);
    tempPredicate->AddId(tempID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::STRING);
    tempParam->Setp(tempID);
    tempParams.push_back(tempParam);
    StringList();
    Match(TokenType::RIGHT_PAREN);
    tempPredicate->SetName(tempText);
    for (unsigned int i = 0; i < tempParams.size(); ++i){
        tempPredicate->AddParameter(tempParams.at(i));
    }
    Match(TokenType::PERIOD);
    // add fact predicates to array
    facts.push_back(tempPredicate);
    tempParams.clear();
    tempText = "";
}

void DatalogProgram::FactList() {
    if (tokenList.at(index)->GetType() == TokenType::RULES){}
        // maybe need else if end of vector
    else{
        Fact();
        FactList();
    }

}

void DatalogProgram::Rule() {
    HeadPredicate();
    auto tempRule = new Rules(tempPred);
    tempRule->AddHeadPredicate(tempPred);
    tempParams.clear();
    tempText = "";
    Match(TokenType::COLON_DASH);
    tempText = "";
    Predicate();
    for (unsigned int i = 0; i < tempParams.size(); ++i){
        tempPred->AddParameter(tempParams.at(i));
    }
    rulePredicates.push_back(tempPred);
    tempParams.clear();
    PredicateList();
    Match(TokenType::PERIOD);
    for (unsigned int i = 0; i < rulePredicates.size(); ++i){
        tempRule->AddBodyPredicate(rulePredicates.at(i));
    }
    rules.push_back(tempRule);
    rulePredicates.clear();
    tempText = "";
    tempParams.clear();

}

void DatalogProgram::RuleList() {
    if (tokenList.at(index)->GetType() == TokenType::QUERIES){}
    else{
        Rule();
        RuleList();
    }
}

void DatalogProgram::Query() {
    Predicate();
    Match(TokenType::Q_MARK);
    for (unsigned int i = 0; i < tempParams.size(); ++i){
        tempPred->AddParameter(tempParams.at(i));
    }
    tempPred->SetName(tempText);
    queries.push_back(tempPred);
    tempText = "";
    tempParams.clear();
}

void DatalogProgram::QueryList() {
    if (tokenList.at(index)->GetType() == TokenType::EOF_ENUM){}
    else{
        Query();
        QueryList();
    }
}

void DatalogProgram::HeadPredicate() {
    auto tempPredicate = new Predicates();
    auto tempParam = new Parameters();
    Match(TokenType::ID);
    tempPredicate->AddId(tempID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    tempParam->Setp(tempID);
    tempParams.push_back(tempParam);
    IdList();
    Match(TokenType::RIGHT_PAREN);
    tempPred = tempPredicate;
    for (unsigned int i = 0; i < tempParams.size(); ++i){
        tempPred->AddParameter(tempParams.at(i));
    }

}

void DatalogProgram::Predicate() {
    auto tempPredicate = new Predicates();
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    tempPredicate->AddId(tempID);
    Parameter();
    ParameterList();
    Match(TokenType::RIGHT_PAREN);
    tempPred = tempPredicate;
}

void DatalogProgram::PredicateList() {
    tempText = "";
    if (tokenList.at(index)->GetType() == TokenType::PERIOD) {}
    else{
        Match(TokenType::COMMA);
        Predicate();
        for (unsigned int i = 0; i < tempParams.size(); ++i){
            tempPred->AddParameter(tempParams.at(i));
        }
        rulePredicates.push_back(tempPred);
        tempParams.clear();
        PredicateList();
    }
}

void DatalogProgram::Parameter() {
    auto tempParam = new Parameters();
    if (tokenList.at(index)->GetType() == TokenType::STRING) {
        Match(TokenType::STRING);
    }
    else{
        Match(TokenType::ID);

    }
    tempParam->Setp(tempID);
    tempParams.push_back(tempParam);
}

void DatalogProgram::ParameterList() {
    if (tokenList.at(index)->GetType() == TokenType::RIGHT_PAREN) {}
    else{
        Match(TokenType::COMMA);
        Parameter();
        ParameterList();
    }
}

void DatalogProgram::IdList() {
    if (tokenList.at(index)->GetType() == TokenType::RIGHT_PAREN){}
    else{
        auto tempParam = new Parameters();
        Match(TokenType::COMMA);
        Match(TokenType::ID);
        tempParam->Setp(tempID);
        tempParams.push_back(tempParam);
        IdList();
    }
}

void DatalogProgram::StringList() {
    if (tokenList.at(index)->GetType() == TokenType::RIGHT_PAREN){}
        // maybe need else if end of vector
    else{
        auto tempParam = new Parameters();
        Match(TokenType::COMMA);
        Match(TokenType::STRING);
        tempParam->Setp(tempID);
        tempParams.push_back(tempParam);
        StringList();
    }
}

void DatalogProgram::FindDomain() {
    for (unsigned int i = 0; i < facts.size(); ++i){
        for (unsigned int j = 0; j < facts.at(i)->GetParameters().size(); ++j){
            domainParams.push_back(facts.at(i)->GetParameters().at(j)->Getp());
        }
    }
    sort( domainParams.begin(), domainParams.end() );
    domainParams.erase( unique( domainParams.begin(), domainParams.end() ), domainParams.end() );
}

std::string DatalogProgram::SchemesToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < schemes.size(); ++i){
        ss << "  " << schemes.at(i)->toString() << std::endl;
    }
    return ss.str();
}

std::string DatalogProgram::FactsToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < facts.size(); ++i){
        ss << "  " << facts.at(i)->toString() << "." << std::endl;
    }
    return ss.str();
}

std::string DatalogProgram::RulesToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < rules.size(); ++i){
        ss << rules.at(i)->toString() << std::endl;
    }
    return ss.str();
}

std::string DatalogProgram::QueriesToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < queries.size(); ++i){
        ss << "  " << queries.at(i)->toString() << "?" << std::endl;
    }

    return ss.str();
}

std::string DatalogProgram::DomainToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < domainParams.size(); ++i){
        ss << "  " << domainParams.at(i) << std::endl;
    }
    return ss.str();
}

std::string DatalogProgram::DatalogToString() {
    std::stringstream ss;
    ss << "Schemes(" << schemes.size() << "):" << std::endl;
    ss << SchemesToString();
    ss << "Facts(" << facts.size() << "):" << std::endl;
    ss << FactsToString();
    ss << "Rules(" << rules.size() << "):" << std::endl;
    ss << RulesToString();
    ss << "Queries(" << queries.size() << "):" << std::endl;
    ss << QueriesToString();
    ss << "Domain(" << domainParams.size() << "):" << std::endl;
    ss << DomainToString();
    return ss.str();
}

std::vector<Predicates*> DatalogProgram::GetSchemes() {
    return schemes;
}

std::vector<Predicates*> DatalogProgram::GetFacts() {
    return facts;
}

std::vector<Predicates*> DatalogProgram::GetQueries() {
    return queries;
}

std::vector<Rules*> DatalogProgram::GetRules() {
    return rules;
}