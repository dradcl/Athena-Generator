#include "Generator.h"
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

std::string profileInfo = "{\"profileRevision\":1,\"profileId\":\"athena\",\"profileChangesBaseRevision\":1,\"profileChanges\":[{\"changeType\":\"fullProfileUpdate\",\"profile\":{\"_id\":\"001\",\"created\":\"2019-12-01T09:18:28.275Z\",\"updated\":\"2020-03-22T18:26:57.808Z\",\"rvn\":1,\"wipeNumber\":1,\"accountId\":\"001\",\"profileId\":\"athena\",\"version\":\"kittenX\",\"items\":{\"3635f67c-00e4-4a04-b8ab-a959a5eb3f13\":{\"templateId\":\"CosmeticLocker:cosmeticlocker_athena\",\"attributes\":{\"locker_slots_data\":{\"slots\":{\"MusicPack\":{\"items\":[\"AthenaMusicPack:MusicPack_Random\"]},\"Character\":{\"items\":[\"AthenaCharacter:CID_Random\"],\"activeVariants\":[null]},\"Backpack\":{\"items\":[\"AthenaBackpack:BID_Random\"],\"activeVariants\":[null]},\"SkyDiveContrail\":{\"items\":[\"AthenaSkyDiveContrail:Trails_Random\"],\"activeVariants\":[null]},\"Dance\":{\"items\":[\"AthenaDance:eid_lasagnadance\",\"AthenaDance:eid_nevergonna\",\"AthenaDance:eid_crabdance\",\"AthenaDance:eid_skeletondance\",\"AthenaDance:eid_grooving\",\"AthenaDance:eid_gabbyhiphop_01\"]},\"LoadingScreen\":{\"items\":[\"AthenaLoadingScreen:LSID_Random\"]},\"Pickaxe\":{\"items\":[\"AthenaPickaxe:Pickaxe_Random\"],\"activeVariants\":[null]},\"Glider\":{\"items\":[\"AthenaGlider:Glider_Random\"],\"activeVariants\":[null]},\"ItemWrap\":{\"items\":[\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\",\"AthenaItemWrap:Wrap_Random\"],\"activeVariants\":[null,null,null,null,null,null,null,null]}}},\"use_count\":0,\"banner_icon_template\":\"foundertier1banner1\",\"banner_color_template\":\"defaultcolor6\",\"locker_name\":\"\",\"item_seen\":false,\"favorite\":false},\"quantity\":1},";

std::string stats = "},\"stats\":{\"attributes\":{\"season_match_boost\":90,\"loadouts\":[\"3635f67c-00e4-4a04-b8ab-a959a5eb3f13\"],\"mfa_reward_claimed\":true,\"rested_xp_overflow\":0,\"quest_manager\":{\"dailyLoginInterval\":\"2020-03-22T09:10:05.624Z\",\"dailyQuestRerolls\":0},\"book_level\":1000,\"season_num\":13,\"book_xp\":0,\"permissions\":[],\"season\":{\"numWins\":38,\"numHighBracket\":95,\"numLowBracket\":213},\"lifetime_wins\":498,\"book_purchased\":true,\"party_assist_quest\":\"efb4927c-cf61-4541-8021-fb9f56dc92ac\",\"purchased_battle_pass_tier_offers\":[{\"id\":\"season7_v1\",\"count\":1}],\"rested_xp_exchange\":1,\"level\":1000,\"xp_overflow\":0,\"rested_xp\":99057,\"rested_xp_mult\":4.25,\"accountLevel\":1145,\"competitive_identity\":{},\"inventory_limit_bonus\":0,\"last_applied_loadout\":\"3635f67c-00e4-4a04-b8ab-a959a5eb3f13\",\"daily_rewards\":{},\"xp\":22481,\"season_friend_match_boost\":0,\"active_loadout_index\":0}},\"commandRevision\":1}}],\"profileCommandRevision\":1,\"serverTime\":\"2020-03-22T18:39:38.712Z\",\"responseVersion\":1}";

std::vector<Item> getItemIds(std::string url)
{
	std::vector<Item> itemsToGen;
	nlohmann::json items;

	cpr::Response resp = cpr::Get(cpr::Url{ url });
	nlohmann::json res = nlohmann::json::parse(resp.text);

	if (url == "https://benbotfn.tk/api/v1/cosmetics/br")
	{
		items = res;
	}
	else
	{
		items = res["items"];
	}
	
	for (auto item : items)
	{
		itemsToGen.push_back(Item(item["id"], item["backendType"]));
	}

	return itemsToGen;
}

void generate(bool newItems) // will redo the duplicate code for each case later
{
	std::ofstream filestream;

	if (newItems)
	{
		std::vector<Item> genItems = getItemIds("https://benbotfn.tk/api/v1/newCosmetics");
		filestream.open("new.json");
		filestream << profileInfo;

		for (unsigned int i = 0; i < genItems.size() - 1; i++)
		{
			filestream << genItems[i].toString() << ",";
		}

		filestream << genItems[genItems.size() - 1].toString() << stats;
		filestream.close();
	}
	else
	{
		std::vector<Item> genItems = getItemIds("https://benbotfn.tk/api/v1/cosmetics/br");
		filestream.open("all.json");
		filestream << profileInfo;

		for (unsigned int i = 0; i < genItems.size() - 1; i++)
		{
			filestream << genItems[i].toString() << ",";
		}

		filestream << genItems[genItems.size() - 1].toString() << stats;
		filestream.close();
	}
}

Item::Item(std::string id, std::string backendType)
{
	this->id = id;
	this->backendType = backendType;
}

std::string Item::toString() // used to write to file in json string format
{
	std::string definition = backendType + ":" + id;
	return "\"" + definition + "\"" + ": {\"templateId\":" + "\"" + definition + "\"" + ",\"attributes\": {\"max_level_bonus\": 0,\"level\": 1,\"item_seen\": 1,\"xp\": 0,\"variants\": [],\"favorite\": \"false\"},\"quantity\": 1}";
}