#pragma once

#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdint>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Personal {
    public:
        Personal(std::string inFile) {
            file = inFile;
            printf("InFile: %s\n", file.c_str());
        }
        
        ~Personal(){
            Entries.clear();
        }
        
        void ExportJson(std::string outFile){
            FILE *fp = fopen(file.c_str(), "rb");
            while(!feof(fp)) {
                PersonalEntry ent;
                fread(&ent, sizeof(PersonalEntry), 1, fp);
                Entries.push_back(ent);
            }
            fclose(fp);
            
            rapidjson::Document document;
            document.SetObject();
            
            rapidjson::Value array(rapidjson::kArrayType);
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
            
            for(auto &e : Entries){
                rapidjson::Value persEntry(rapidjson::kObjectType);
                
                //Base stats
                rapidjson::Value stat(rapidjson::kObjectType);
                stat.AddMember("HP", e.HP, allocator);
                stat.AddMember("ATK", e.ATK, allocator);
                stat.AddMember("DEF", e.DEF, allocator);
                stat.AddMember("SPE", e.SPE, allocator);
                stat.AddMember("SPA", e.SPA, allocator);
                stat.AddMember("SPD", e.SPD, allocator);
                persEntry.AddMember("Base stats", stat, allocator);
                
                //Types
                persEntry.AddMember("Type1", e.Type1, allocator);
                persEntry.AddMember("Type2", e.Type2, allocator);
                
                //Catch/Evo
                persEntry.AddMember("CatchRate", e.CatchRate, allocator);
                persEntry.AddMember("EvoStage", e.EvoStage, allocator);
                
                //EVs
                rapidjson::Value ev(rapidjson::kObjectType);
                ev.AddMember("EV_HP", (e.EVYield >> 0) & 3, allocator);
                ev.AddMember("EV_ATK", (e.EVYield >> 2) & 3, allocator);
                ev.AddMember("EV_DEF", (e.EVYield >> 4) & 3, allocator);
                ev.AddMember("EV_SPE", (e.EVYield >> 6) & 3, allocator);
                ev.AddMember("EV_SPA", (e.EVYield >> 8) & 3, allocator);
                ev.AddMember("EV_SPD", (e.EVYield >> 10) & 3, allocator);
                ev.AddMember("EV_UNK", (e.EVYield >> 12) & 3, allocator);
                persEntry.AddMember("EVs", ev, allocator);
                
                //Misc
                persEntry.AddMember("Item1", e.Item1, allocator);
                persEntry.AddMember("Item2", e.Item2, allocator);
                persEntry.AddMember("Item3", e.Item3, allocator);
                persEntry.AddMember("Gender", e.Gender, allocator);
                persEntry.AddMember("HatchCycles", e.HatchCycles, allocator);
                persEntry.AddMember("BaseFriendship", e.BaseFriendship, allocator);
                persEntry.AddMember("EXPGrowth", e.EXPGrowth, allocator);
                persEntry.AddMember("EggGroup1", e.EggGroup1, allocator);
                persEntry.AddMember("EggGroup2", e.EggGroup2, allocator);
                persEntry.AddMember("Ability1", e.Ability1, allocator);
                persEntry.AddMember("Ability2", e.Ability2, allocator);
                persEntry.AddMember("AbilityH", e.AbilityH, allocator);
                persEntry.AddMember("FormeSprite", e.FormeSprite, allocator);
                persEntry.AddMember("FormeCount", e.FormeCount, allocator);
                persEntry.AddMember("Color", e.IsPresentInGame & 0x3F, allocator);
                persEntry.AddMember("IsPresentInGame", (bool)((e.IsPresentInGame >> 6) & 1), allocator);
                persEntry.AddMember("BaseEXP", e.BaseEXP, allocator);
                persEntry.AddMember("Height", e.Height, allocator);
                persEntry.AddMember("Weight", e.Weight, allocator);
                
                //unk group
                persEntry.AddMember("field_28", e.field_28, allocator);
                persEntry.AddMember("field_29", e.field_29, allocator);
                persEntry.AddMember("field_2A", e.field_2A, allocator);
                persEntry.AddMember("field_2B", e.field_2B, allocator);
                persEntry.AddMember("field_2C", e.field_2C, allocator);
                persEntry.AddMember("field_2D", e.field_2D, allocator);
                persEntry.AddMember("field_2E", e.field_2E, allocator);
                persEntry.AddMember("field_2F", e.field_2F, allocator);
                persEntry.AddMember("field_30", e.field_30, allocator);
                persEntry.AddMember("field_31", e.field_31, allocator);
                persEntry.AddMember("field_32", e.field_32, allocator);
                persEntry.AddMember("field_33", e.field_33, allocator);
                persEntry.AddMember("field_34", e.field_34, allocator);
                persEntry.AddMember("field_35", e.field_35, allocator);
                persEntry.AddMember("field_36", e.field_36, allocator);
                persEntry.AddMember("field_37", e.field_37, allocator);
                persEntry.AddMember("field_38", e.field_38, allocator);
                persEntry.AddMember("field_3A", e.field_3A, allocator);
                persEntry.AddMember("field_3C", e.field_3C, allocator);
                persEntry.AddMember("field_3D", e.field_3D, allocator);
                persEntry.AddMember("field_3E", e.field_3E, allocator);
                persEntry.AddMember("field_3F", e.field_3F, allocator);
                persEntry.AddMember("field_40", e.field_40, allocator);
                persEntry.AddMember("field_41", e.field_41, allocator);
                persEntry.AddMember("field_42", e.field_42, allocator);
                persEntry.AddMember("field_43", e.field_43, allocator);
                persEntry.AddMember("field_44", e.field_44, allocator);
                persEntry.AddMember("field_45", e.field_45, allocator);
                persEntry.AddMember("field_46", e.field_46, allocator);
                persEntry.AddMember("field_47", e.field_47, allocator);
                persEntry.AddMember("field_48", e.field_48, allocator);
                persEntry.AddMember("field_4A", e.field_4A, allocator);
                
                persEntry.AddMember("Icon", e.Icon, allocator);
                
                persEntry.AddMember("unused_4E", e.unused_4E, allocator);
                persEntry.AddMember("unused_50", e.unused_50, allocator);
                persEntry.AddMember("field_52", e.field_52, allocator);
                persEntry.AddMember("field_54", e.field_54, allocator);
                
                persEntry.AddMember("EvoBaseID", e.EvoBaseID, allocator);
                
                persEntry.AddMember("FormIndex", e.FormIndex, allocator);
                persEntry.AddMember("IsGalarianForm", (bool)(e.GalarianFormField & 1), allocator);
                persEntry.AddMember("IsEventMon", (bool)((e.GalarianFormField >> 2) & 1), allocator);
                persEntry.AddMember("DexNumber", e.DexNumber, allocator);

                persEntry.AddMember("field_5E", e.field_5E, allocator);
                persEntry.AddMember("field_60", e.field_60, allocator);
                persEntry.AddMember("field_61", e.field_61, allocator);
                persEntry.AddMember("field_62", e.field_62, allocator);
                persEntry.AddMember("field_63", e.field_63, allocator);
                persEntry.AddMember("field_64", e.field_64, allocator);
                persEntry.AddMember("field_65", e.field_65, allocator);
                persEntry.AddMember("field_66", e.field_66, allocator);
                persEntry.AddMember("field_67", e.field_67, allocator);
                persEntry.AddMember("field_68", e.field_68, allocator);
                persEntry.AddMember("field_6A", e.field_6A, allocator);
                persEntry.AddMember("field_6B", e.field_6B, allocator);
                persEntry.AddMember("field_6C", e.field_6C, allocator);
                persEntry.AddMember("field_6D", e.field_6D, allocator);
                persEntry.AddMember("field_6E", e.field_6E, allocator);
                persEntry.AddMember("field_6F", e.field_6F, allocator);
                persEntry.AddMember("field_70", e.field_70, allocator);
                persEntry.AddMember("field_71", e.field_71, allocator);
                persEntry.AddMember("field_72", e.field_72, allocator);
                persEntry.AddMember("field_73", e.field_73, allocator);
                persEntry.AddMember("field_74", e.field_74, allocator);
                persEntry.AddMember("field_75", e.field_75, allocator);
                persEntry.AddMember("field_76", e.field_76, allocator);
                persEntry.AddMember("field_77", e.field_77, allocator);
                persEntry.AddMember("field_78", e.field_78, allocator);
                persEntry.AddMember("field_79", e.field_79, allocator);
                persEntry.AddMember("field_7A", e.field_7A, allocator);
                persEntry.AddMember("field_7B", e.field_7B, allocator);
                persEntry.AddMember("field_7C", e.field_7C, allocator);
                persEntry.AddMember("field_7D", e.field_7D, allocator);
                persEntry.AddMember("field_7E", e.field_7E, allocator);
                persEntry.AddMember("field_7F", e.field_7F, allocator);
                persEntry.AddMember("field_80", e.field_80, allocator);
                persEntry.AddMember("field_81", e.field_81, allocator);
                persEntry.AddMember("field_82", e.field_82, allocator);
                
                
                rapidjson::Value unkg(rapidjson::kObjectType);                
                unkg.AddMember("field_83", e.field_83, allocator);
                unkg.AddMember("field_84", e.field_84, allocator);
                unkg.AddMember("field_85", e.field_85, allocator);
                unkg.AddMember("field_86", e.field_86, allocator);
                unkg.AddMember("field_87", e.field_87, allocator);
                unkg.AddMember("field_88", e.field_88, allocator);
                unkg.AddMember("field_89", e.field_89, allocator);
                unkg.AddMember("field_8A", e.field_8A, allocator);
                unkg.AddMember("field_8B", e.field_8B, allocator);
                unkg.AddMember("field_8C", e.field_8C, allocator);
                unkg.AddMember("field_8D", e.field_8D, allocator);
                unkg.AddMember("field_8E", e.field_8E, allocator);
                unkg.AddMember("field_8F", e.field_8F, allocator);
                unkg.AddMember("field_90", e.field_90, allocator);
                unkg.AddMember("field_91", e.field_91, allocator);
                persEntry.AddMember("Unknown", unkg, allocator);
                
                persEntry.AddMember("field_92", e.field_92, allocator);
                persEntry.AddMember("field_94", e.field_94, allocator);
                persEntry.AddMember("field_96", e.field_96, allocator);
                persEntry.AddMember("field_98", e.field_98, allocator);
                persEntry.AddMember("field_9A", e.field_9A, allocator);
                persEntry.AddMember("field_9C", e.field_9C, allocator);
                persEntry.AddMember("field_9E", e.field_9E, allocator);
                persEntry.AddMember("field_A0", e.field_A0, allocator);
                persEntry.AddMember("field_A2", e.field_A2, allocator);
                persEntry.AddMember("field_A4", e.field_A4, allocator);
                persEntry.AddMember("Unused_A6", e.Unused_A6, allocator);
                
                array.PushBack(persEntry, allocator);
            }
            document.AddMember("Entries", array, allocator);
            
            rapidjson::StringBuffer strbuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
            document.Accept(writer);
            
            fp = fopen(outFile.c_str(), "w");
            fwrite(strbuf.GetString(), strbuf.Size(), 1, fp);
            fclose(fp);
        }
        
        void ExportBinary(std::string outFile) {
            std::ifstream in(file);
            std::string json((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            
            rapidjson::Document document;
            if (document.Parse<0>(json.c_str()).HasParseError()){
                printf("Error parsing json\n");
                return;
            }
            
            const rapidjson::Value& ents = document["Entries"];
            FILE *fp = fopen(outFile.c_str(), "wb");
            for(rapidjson::SizeType i = 0; i < ents.Size() - 1; i++) {
                PersonalEntry pent;
                memset(&pent, 0, sizeof(PersonalEntry));
                
                //Base stats
                pent.HP = ents[i]["Base stats"]["HP"].GetInt();
                pent.ATK = ents[i]["Base stats"]["ATK"].GetInt();
                pent.DEF = ents[i]["Base stats"]["DEF"].GetInt();
                pent.SPE = ents[i]["Base stats"]["SPE"].GetInt();
                pent.SPA = ents[i]["Base stats"]["SPA"].GetInt();
                pent.SPD = ents[i]["Base stats"]["SPD"].GetInt();
                
                pent.Type1 = ents[i]["Type1"].GetInt();
                pent.Type2 = ents[i]["Type2"].GetInt();
                pent.CatchRate = ents[i]["CatchRate"].GetUint();
                pent.EvoStage = ents[i]["EvoStage"].GetUint();
                
                pent.EVYield = (ents[i]["EVs"]["EV_HP"].GetUint() & 3);
                pent.EVYield |= ((ents[i]["EVs"]["EV_ATK"].GetUint() & 3) << 2);
                pent.EVYield |= ((ents[i]["EVs"]["EV_DEF"].GetUint() & 3) << 4);
                pent.EVYield |= ((ents[i]["EVs"]["EV_SPE"].GetUint() & 3) << 6);
                pent.EVYield |= ((ents[i]["EVs"]["EV_SPA"].GetUint() & 3) << 8);
                pent.EVYield |= ((ents[i]["EVs"]["EV_SPD"].GetUint() & 3) << 10);
                pent.EVYield |= ((ents[i]["EVs"]["EV_UNK"].GetUint() & 3) << 12);
                
                pent.Item1 = ents[i]["Item1"].GetInt();
                pent.Item2 = ents[i]["Item2"].GetInt();
                pent.Item3 = ents[i]["Item3"].GetInt();
                pent.Gender = ents[i]["Gender"].GetInt();
                pent.HatchCycles = ents[i]["HatchCycles"].GetInt();
                pent.BaseFriendship = ents[i]["BaseFriendship"].GetInt();
                pent.EXPGrowth = ents[i]["EXPGrowth"].GetInt();
                pent.EXPGrowth = ents[i]["EXPGrowth"].GetInt();
                pent.EggGroup1 = ents[i]["EggGroup1"].GetInt();
                pent.EggGroup2 = ents[i]["EggGroup2"].GetInt();
                pent.Ability1 = ents[i]["Ability1"].GetUint();
                pent.Ability2 = ents[i]["Ability2"].GetUint();
                pent.AbilityH = ents[i]["AbilityH"].GetUint();
                pent.FormeSprite = ents[i]["FormeSprite"].GetUint();
                pent.FormeCount = ents[i]["FormeCount"].GetInt();
                pent.IsPresentInGame = (ents[i]["IsPresentInGame"].GetBool() << 6);
                pent.IsPresentInGame |= (ents[i]["Color"].GetInt() & 0x3F);
                pent.BaseEXP = ents[i]["BaseEXP"].GetUint();
                pent.Height = ents[i]["Height"].GetUint();
                pent.Weight = ents[i]["Weight"].GetUint();
                pent.field_28 = ents[i]["field_28"].GetUint();
                pent.field_29 = ents[i]["field_29"].GetUint();
                pent.field_2A = ents[i]["field_2A"].GetUint();
                pent.field_2B = ents[i]["field_2B"].GetUint();
                pent.field_2C = ents[i]["field_2C"].GetUint();
                pent.field_2D = ents[i]["field_2D"].GetUint();
                pent.field_2E = ents[i]["field_2E"].GetUint();
                pent.field_2F = ents[i]["field_2F"].GetUint();
                pent.field_30 = ents[i]["field_30"].GetUint();
                pent.field_31 = ents[i]["field_31"].GetUint();
                pent.field_32 = ents[i]["field_32"].GetUint();
                pent.field_33 = ents[i]["field_33"].GetUint();
                pent.field_34 = ents[i]["field_34"].GetUint();
                pent.field_35 = ents[i]["field_35"].GetUint();
                pent.field_36 = ents[i]["field_36"].GetUint();
                pent.field_37 = ents[i]["field_37"].GetUint();
                pent.field_38 = ents[i]["field_38"].GetUint();
                pent.field_3A = ents[i]["field_3A"].GetUint();
                pent.field_3C = ents[i]["field_3C"].GetUint();
                pent.field_3D = ents[i]["field_3D"].GetUint();
                pent.field_3E = ents[i]["field_3E"].GetUint();
                pent.field_3F = ents[i]["field_3F"].GetUint();
                pent.field_40 = ents[i]["field_40"].GetUint();
                pent.field_41 = ents[i]["field_41"].GetUint();
                pent.field_42 = ents[i]["field_42"].GetUint();
                pent.field_43 = ents[i]["field_43"].GetUint();
                pent.field_44 = ents[i]["field_44"].GetUint();
                pent.field_45 = ents[i]["field_45"].GetUint();
                pent.field_46 = ents[i]["field_46"].GetUint();
                pent.field_47 = ents[i]["field_47"].GetUint();
                pent.field_48 = ents[i]["field_48"].GetUint();
                pent.field_4A = ents[i]["field_4A"].GetUint();
                pent.Icon = ents[i]["Icon"].GetUint();
                pent.unused_4E = ents[i]["unused_4E"].GetUint();
                pent.unused_50 = ents[i]["unused_50"].GetUint();
                pent.field_52 = ents[i]["field_52"].GetUint();
                pent.field_54 = ents[i]["field_54"].GetUint();
                pent.EvoBaseID = ents[i]["EvoBaseID"].GetUint();
                pent.FormIndex = ents[i]["FormIndex"].GetUint();
                pent.GalarianFormField = (ents[i]["IsEventMon"].GetBool() << 2);
                pent.GalarianFormField = ents[i]["IsGalarianForm"].GetBool();
                pent.DexNumber = ents[i]["DexNumber"].GetUint();
                pent.field_5E = ents[i]["field_5E"].GetUint();
                pent.field_60 = ents[i]["field_60"].GetUint();
                pent.field_61 = ents[i]["field_61"].GetUint();
                pent.field_62 = ents[i]["field_62"].GetUint();
                pent.field_63 = ents[i]["field_63"].GetUint();
                pent.field_64 = ents[i]["field_64"].GetUint();
                pent.field_65 = ents[i]["field_65"].GetUint();
                pent.field_66 = ents[i]["field_66"].GetUint();
                pent.field_67 = ents[i]["field_67"].GetUint();
                pent.field_68 = ents[i]["field_68"].GetUint();
                pent.field_6A = ents[i]["field_6A"].GetUint();
                pent.field_6B = ents[i]["field_6B"].GetUint();
                pent.field_6C = ents[i]["field_6C"].GetUint();
                pent.field_6D = ents[i]["field_6D"].GetUint();
                pent.field_6E = ents[i]["field_6E"].GetUint();
                pent.field_6F = ents[i]["field_6F"].GetUint();
                pent.field_70 = ents[i]["field_70"].GetUint();
                pent.field_71 = ents[i]["field_71"].GetUint();
                pent.field_72 = ents[i]["field_72"].GetUint();
                pent.field_73 = ents[i]["field_73"].GetUint();
                pent.field_74 = ents[i]["field_74"].GetUint();
                pent.field_75 = ents[i]["field_75"].GetUint();
                pent.field_76 = ents[i]["field_76"].GetUint();
                pent.field_77 = ents[i]["field_77"].GetUint();
                pent.field_78 = ents[i]["field_78"].GetUint();
                pent.field_79 = ents[i]["field_79"].GetUint();
                pent.field_7A = ents[i]["field_7A"].GetUint();
                pent.field_7B = ents[i]["field_7B"].GetUint();
                pent.field_7C = ents[i]["field_7C"].GetUint();
                pent.field_7D = ents[i]["field_7D"].GetUint();
                pent.field_7E = ents[i]["field_7E"].GetUint();
                pent.field_7F = ents[i]["field_7F"].GetUint();
                pent.field_80 = ents[i]["field_80"].GetUint();
                pent.field_81 = ents[i]["field_81"].GetUint();
                pent.field_82 = ents[i]["field_82"].GetUint();
                pent.field_83 = ents[i]["Unknown"]["field_83"].GetUint();
                pent.field_84 = ents[i]["Unknown"]["field_84"].GetUint();
                pent.field_85 = ents[i]["Unknown"]["field_85"].GetUint();
                pent.field_86 = ents[i]["Unknown"]["field_86"].GetUint();
                pent.field_87 = ents[i]["Unknown"]["field_87"].GetUint();
                pent.field_88 = ents[i]["Unknown"]["field_88"].GetUint();
                pent.field_89 = ents[i]["Unknown"]["field_89"].GetUint();
                pent.field_8A = ents[i]["Unknown"]["field_8A"].GetUint();
                pent.field_8B = ents[i]["Unknown"]["field_8B"].GetUint();
                pent.field_8C = ents[i]["Unknown"]["field_8C"].GetUint();
                pent.field_8D = ents[i]["Unknown"]["field_8D"].GetUint();
                pent.field_8E = ents[i]["Unknown"]["field_8E"].GetUint();
                pent.field_8F = ents[i]["Unknown"]["field_8F"].GetUint();
                pent.field_90 = ents[i]["Unknown"]["field_90"].GetUint();
                pent.field_91 = ents[i]["Unknown"]["field_91"].GetUint();
                pent.field_92 = ents[i]["field_92"].GetUint();
                pent.field_94 = ents[i]["field_94"].GetUint();
                pent.field_96 = ents[i]["field_96"].GetUint();
                pent.field_98 = ents[i]["field_98"].GetUint();
                pent.field_9A = ents[i]["field_9A"].GetUint();
                pent.field_9C = ents[i]["field_9C"].GetUint();
                pent.field_9E = ents[i]["field_9E"].GetUint();
                pent.field_A0 = ents[i]["field_A0"].GetUint();
                pent.field_A2 = ents[i]["field_A2"].GetUint();
                pent.field_A4 = ents[i]["field_A4"].GetUint();
                pent.Unused_A6 = ents[i]["Unused_A6"].GetUint();
                
                fwrite(&pent, sizeof(PersonalEntry), 1, fp);
            }
            fclose(fp);
        }
        
    private:
        #pragma pack(push, 1)
        typedef struct PersonalEntry {
            uint8_t HP;
            uint8_t ATK;
            uint8_t DEF;
            uint8_t SPE;
            uint8_t SPA;
            uint8_t SPD;
            int8_t Type1;
            int8_t Type2;
            uint8_t CatchRate;
            uint8_t EvoStage;
            uint16_t EVYield;
            uint16_t Item1;
            uint16_t Item2;
            uint16_t Item3;
            int8_t Gender;
            int8_t HatchCycles;
            int8_t BaseFriendship;
            int8_t EXPGrowth;
            int8_t EggGroup1;
            int8_t EggGroup2;
            uint16_t Ability1;
            uint16_t Ability2;
            uint16_t AbilityH;
            uint16_t FormeSprite;
            int8_t FormeCount;
            uint8_t IsPresentInGame;
            uint16_t BaseEXP;
            uint16_t Height;
            uint16_t Weight;
            uint8_t field_28;
            uint8_t field_29;
            uint8_t field_2A;
            uint8_t field_2B;
            uint8_t field_2C;
            uint8_t field_2D;
            uint8_t field_2E;
            uint8_t field_2F;
            uint8_t field_30;
            uint8_t field_31;
            uint8_t field_32;
            uint8_t field_33;
            uint8_t field_34;
            uint8_t field_35;
            uint8_t field_36;
            uint8_t field_37;
            uint16_t field_38;
            uint16_t field_3A;
            uint8_t field_3C;
            uint8_t field_3D;
            uint8_t field_3E;
            uint8_t field_3F;
            uint8_t field_40;
            uint8_t field_41;
            uint8_t field_42;
            uint8_t field_43;
            uint8_t field_44;
            uint8_t field_45;
            uint8_t field_46;
            uint8_t field_47;
            uint16_t field_48;
            uint16_t field_4A;
            uint16_t Icon;
            uint16_t unused_4E;
            uint16_t unused_50;
            uint16_t field_52;
            uint16_t field_54;
            uint16_t EvoBaseID;
            uint16_t FormIndex;
            uint16_t GalarianFormField;
            uint16_t DexNumber;
            uint16_t field_5E;
            uint8_t field_60;
            uint8_t field_61;
            uint8_t field_62;
            uint8_t field_63;
            uint8_t field_64;
            uint8_t field_65;
            uint8_t field_66;
            uint8_t field_67;
            uint16_t field_68;
            uint8_t field_6A;
            uint8_t field_6B;
            uint8_t field_6C;
            uint8_t field_6D;
            uint8_t field_6E;
            uint8_t field_6F;
            uint8_t field_70;
            uint8_t field_71;
            uint8_t field_72;
            uint8_t field_73;
            uint8_t field_74;
            uint8_t field_75;
            uint8_t field_76;
            uint8_t field_77;
            uint8_t field_78;
            uint8_t field_79;
            uint8_t field_7A;
            uint8_t field_7B;
            uint8_t field_7C;
            uint8_t field_7D;
            uint8_t field_7E;
            uint8_t field_7F;
            uint8_t field_80;
            uint8_t field_81;
            uint8_t field_82;
            uint8_t field_83;
            uint8_t field_84;
            uint8_t field_85;
            uint8_t field_86;
            uint8_t field_87;
            uint8_t field_88;
            uint8_t field_89;
            uint8_t field_8A;
            uint8_t field_8B;
            uint8_t field_8C;
            uint8_t field_8D;
            uint8_t field_8E;
            uint8_t field_8F;
            uint8_t field_90;
            uint8_t field_91;
            uint16_t field_92;
            uint16_t field_94;
            uint16_t field_96;
            uint16_t field_98;
            uint16_t field_9A;
            uint16_t field_9C;
            uint16_t field_9E;
            uint16_t field_A0;
            uint16_t field_A2;
            uint16_t field_A4;
            uint16_t Unused_A6;
        } PersonalEntry;
        #pragma pack(pop)
        std::vector<PersonalEntry> Entries;
        std::string file;
        static_assert (sizeof(PersonalEntry) == 0xA8, "Size is not correct");
};